#!/usr/bin/env python3
"""Run the notebook's tests.

  python3 test.py                 build and run every tests/**/*.cpp
  python3 test.py suffix lca      only tests whose path contains one of the words
  python3 test.py --fast          no sanitizers (-O2), for quick iteration
  python3 test.py --perf          only the performance tests (tests/perf/)
  python3 test.py --no-perf       skip the performance tests
  python3 test.py --coverage      list C++ snippets that no test includes

Performance tests (tests/perf/) are always built like a contest submission
(-O2, no sanitizers) and run one at a time after the others, so timings are
not disturbed. Each PERF(name, ms) block must finish within ms milliseconds
times $PERF_SCALE (default 1; raise it on a slower machine). CI skips them.

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


def flags(fast, perf=False):
    base = ["-std=c++20", "-g", "-Wall", "-Wextra", "-Wno-sign-compare", "-Wno-format-zero-length",
            "-include", str(ROOT / "tests/common.h"),
            "-I", str(ROOT / "snippets"), "-I", str(ROOT / "tests")]
    if perf:
        return base[:1] + base[2:] + ["-O2"]
    if fast:
        return base + ["-O2"]
    return base + ["-O1", "-fsanitize=address,undefined", "-fno-sanitize-recover=all",
                   "-D_GLIBCXX_ASSERTIONS"]


VARIANTS_RE = re.compile(r"^// variants: (\S+) (\S+)", re.M)


def variants(path):
    """For a test with `// variants: BASE.h FRAG.frag`: one generated header per
    `// == name ==` block of FRAG, with BASE's marked (//!) block replaced by it."""
    m = VARIANTS_RE.search(path.read_text())
    if not m:
        return None
    base = (ROOT / "snippets" / m.group(1)).read_text().split("\n")
    marked = [i for i, l in enumerate(base) if l.rstrip().endswith("//!")]
    lo, hi = marked[0], marked[-1]
    assert marked == list(range(lo, hi + 1)), f"{m.group(1)}: marked lines must be contiguous"
    frag = (ROOT / "snippets" / m.group(2)).read_text()
    frag = re.sub(r"\A\s*/\*\*.*?\*/\s*\n", "", frag, flags=re.S)
    parts = re.split(r"^// == (.*?) ==[ \t]*$", frag, flags=re.M)[1:]
    out = []
    for k in range(0, len(parts), 2):
        body = parts[k + 1].strip("\n").split("\n")
        f = OUT / "gen" / f"{path.stem}_{k // 2}.h"
        f.parent.mkdir(parents=True, exist_ok=True)
        src = "\n".join(base[:lo] + body + base[hi + 1:])
        if not f.exists() or f.read_text() != src:  # keep the mtime: no needless rebuilds
            f.write_text(src)
        out.append((parts[k], f))
    return out


def compile_run(path, exe, extra, deps, fast, perf=False):
    if not exe.exists() or exe.stat().st_mtime < max(d.stat().st_mtime for d in deps):
        c = subprocess.run([gxx(), *flags(fast, perf), *extra, str(path), "-o", str(exe)],
                           capture_output=True, text=True)
        if c.returncode != 0:
            return "COMPILE", c.stderr
    try:
        r = subprocess.run([str(exe)], capture_output=True, text=True, timeout=TIMEOUT,
                           env={**os.environ, "ASAN_OPTIONS": "detect_leaks=0"})
    except subprocess.TimeoutExpired:
        return "TIMEOUT", ""
    return ("ok" if r.returncode == 0 else "FAIL"), (r.stderr + r.stdout)[-3000:]


def is_perf(path):
    return path.relative_to(ROOT / "tests").parts[0] == "perf"


def run_one(path, fast):
    rel = path.relative_to(ROOT / "tests")
    perf = is_perf(path)
    exe = OUT / ("perf" if perf else "fast" if fast else "san") / rel.with_suffix("")
    exe.parent.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    deps = [path, ROOT / "tests/common.h", ROOT / "tests/testlib.h", *included(path)]
    vs = variants(path)
    if vs is None:
        status, log = compile_run(path, exe, [], deps, fast, perf)
        return rel, status, log, time.time() - t0
    for i, (name, header) in enumerate(vs):
        status, log = compile_run(path, exe.with_name(f"{exe.name}_{i}"),
                                  [f"-DVARIANT={i}", f'-DVARIANT_FILE="{header}"'],
                                  deps + [header], fast)
        if status != "ok":
            return rel, status, f"variant '{name}':\n{log}", time.time() - t0
    return rel, "ok", "", time.time() - t0


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
        m = VARIANTS_RE.search(t.read_text())
        if m:
            covered |= {(ROOT / "snippets" / g).resolve() for g in m.groups()}
    missing = []
    for ch in cfg["chapter"]:
        for f in ch["files"]:
            p = (ROOT / "snippets" / ch["dir"] / f.lstrip("+")).resolve()
            if p.suffix in (".h", ".hpp", ".frag") and p not in covered:
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
    if "--perf" in sys.argv:
        tests = [p for p in tests if is_perf(p)]
    if "--no-perf" in sys.argv:
        tests = [p for p in tests if not is_perf(p)]
    if not tests:
        sys.exit("no tests matched")
    failed = 0

    def report(rel, status, log, dt, show):
        nonlocal failed
        print(f"  {status:7} {rel}  ({dt:.1f}s)")
        if status != "ok":
            failed += 1
        if status != "ok" or show:
            print("\n".join("      " + l for l in log.strip().splitlines()[-25:]))

    normal = [p for p in tests if not is_perf(p)]
    with cf.ThreadPoolExecutor(max(1, (os.cpu_count() or 2))) as ex:
        for res in ex.map(lambda p: run_one(p, fast), normal):
            report(*res, show=False)
    for p in tests:  # one at a time, so the timings are not disturbed
        if is_perf(p):
            report(*run_one(p, fast), show=True)
    print(f"{len(tests) - failed}/{len(tests)} passed")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
