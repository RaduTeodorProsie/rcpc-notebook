#!/usr/bin/env python3
"""Run the notebook's tests.

  python3 test.py                 build and run every tests/**/*.cpp
  python3 test.py suffix lca      only tests whose path contains one of the words
  python3 test.py --fast          no sanitizers (-O2), for quick iteration
  python3 test.py --coverage      list C++ snippets that no test includes

Each test is one C++ file that #includes the snippets it exercises (paths
relative to snippets/) plus "testlib.h". It is compiled with
-include tests/common.h (the template prelude), so snippets see the same
macros as in a contest. A test passes if it exits with status 0.
"""
import concurrent.futures as cf
import os
import pathlib
import re
import shutil
import subprocess
import sys
import time
import tomllib

ROOT = pathlib.Path(__file__).resolve().parent
OUT = ROOT / "build" / "tests"
TIMEOUT = 120


def gxx():
    for c in ("g++-16", "g++-15", "g++-14", "g++-13", "g++"):
        if shutil.which(c):
            return c
    sys.exit("no g++ found")


def flags(fast):
    base = ["-std=c++20", "-g", "-Wall", "-Wextra", "-Wno-sign-compare", "-Wno-format-zero-length",
            "-include", str(ROOT / "tests/common.h"),
            "-I", str(ROOT / "snippets"), "-I", str(ROOT / "tests")]
    if fast:
        return base + ["-O2"]
    return base + ["-O1", "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
                   "-D_GLIBCXX_ASSERTIONS"]


def run_one(path, fast):
    rel = path.relative_to(ROOT / "tests")
    exe = OUT / ("fast" if fast else "san") / rel.with_suffix("")
    exe.parent.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    deps = [path, ROOT / "tests/common.h", ROOT / "tests/testlib.h", *included(path)]
    if not exe.exists() or exe.stat().st_mtime < max(d.stat().st_mtime for d in deps):
        c = subprocess.run([gxx(), *flags(fast), str(path), "-o", str(exe)],
                           capture_output=True, text=True)
        if c.returncode != 0:
            return rel, "COMPILE", c.stderr, time.time() - t0
    try:
        r = subprocess.run([str(exe)], capture_output=True, text=True, timeout=TIMEOUT,
                           env={**os.environ, "ASAN_OPTIONS": "detect_leaks=0"})
    except subprocess.TimeoutExpired:
        return rel, "TIMEOUT", "", time.time() - t0
    status = "ok" if r.returncode == 0 else "FAIL"
    return rel, status, (r.stderr + r.stdout)[-3000:], time.time() - t0


def included(path, seen=None):
    """Snippet files a test pulls in, transitively."""
    seen = set() if seen is None else seen
    for inc in re.findall(r'#include\s+"([^"]+)"', path.read_text()):
        for base in (path.parent, ROOT / "snippets", ROOT / "tests"):
            p = (base / inc).resolve()
            if p.exists() and p not in seen:
                seen.add(p)
                included(p, seen)
                break
    return seen


def coverage():
    cfg = tomllib.loads((ROOT / "notebook.toml").read_text())
    covered = set()
    for t in (ROOT / "tests").rglob("*.cpp"):
        covered |= included(t)
    missing = []
    for ch in cfg["chapter"]:
        for f in ch["files"]:
            p = (ROOT / "snippets" / ch["dir"] / f).resolve()
            if p.suffix in (".h", ".hpp") and p not in covered:
                missing.append(f"{ch['dir']}/{f}")
    print("snippets without a test:" if missing else "every .h snippet is tested")
    for m in missing:
        print("  ", m)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if "--coverage" in sys.argv:
        return coverage()
    fast = "--fast" in sys.argv
    tests = sorted(p for p in (ROOT / "tests").rglob("*.cpp")
                   if not args or any(a in str(p.relative_to(ROOT / "tests")) for a in args))
    if not tests:
        sys.exit("no tests matched")
    failed = 0
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 2))) as ex:
        for rel, status, log, dt in ex.map(lambda p: run_one(p, fast), tests):
            print(f"  {status:7} {rel}  ({dt:.1f}s)")
            if status != "ok":
                failed += 1
                print("\n".join("      " + l for l in log.strip().splitlines()[-25:]))
    print(f"{len(tests) - failed}/{len(tests)} passed")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
