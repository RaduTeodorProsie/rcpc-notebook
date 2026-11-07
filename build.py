#!/usr/bin/env python3
"""Build the team notebook.

  python3 build.py            parse snippets, write build/data.json, compile notebook.pdf
  python3 build.py --check    also syntax-check every C++ snippet with g++
  python3 build.py --png      also render build/page-N.png previews

Snippet format (KACTL-compatible header):

  /**
   * Name: Lazy segment tree        (defaults to the file name)
   * Description: free text, Typst markup ($math$, `code`)
   * Time: $O(log n)$
   * Usage: verbatim, may span several lines
   */
  #pragma once                     (hidden)
  #include "point.h"               (hidden, shown as "Needs: point")
  ...code...                       lines ending in //! are shaded (edit here)
                                   and left out of the hash
  // --- uses ---                  optional: everything below is the Uses block
  ...short functions built on the code above...

Shell/Python files use leading `# Key: value` lines, .typ files `// Name: ...`,
.vim files `" Name: ...`.
"""
import hashlib
import json
import pathlib
import platform
import re
import shutil
import subprocess
import sys
import textwrap
import tomllib

ROOT = pathlib.Path(__file__).resolve().parent
BUILD = ROOT / "build"
LANG = {".cpp": "cpp", ".h": "cpp", ".hpp": "cpp", ".frag": "cpp", ".sh": "bash", ".py": "python",
        ".typ": "typ", ".vim": "vim"}  # .frag: C++ fragment (not compiled on its own)
FIELDS = {"name", "description", "time", "memory", "usage", "needs", "status",
          "author", "date", "source", "license"}
SHOWN = ["name", "description", "time", "memory", "usage"]
USES_RE = re.compile(r"^\s*//\s*-+\s*uses\s*-+\s*$", re.I | re.M)
MARK_RE = re.compile(r"\s*//!\s*$")
INCLUDE_RE = re.compile(r'^\s*#include\s+"([^"]+)"\s*\n', re.M)


def parse_fields(lines):
    meta, key = {}, None
    for raw in lines:
        m = re.match(r"\s*([A-Za-z]+):\s?(.*)$", raw)
        if m and m.group(1).lower() in FIELDS:
            key = m.group(1).lower()
            meta[key] = m.group(2).rstrip()
        elif key is not None and raw.strip():
            if key == "usage":
                meta[key] += "\n" + raw.rstrip()
            else:
                meta[key] += " " + raw.strip()
    if "usage" in meta:  # continuation lines carry the header's indent: drop it
        first, *rest = meta["usage"].split("\n")
        meta["usage"] = "\n".join([first, *textwrap.dedent("\n".join(rest)).split("\n")]) if rest else first
    return meta


def split_header(path, text):
    ext = path.suffix
    if LANG.get(ext) == "cpp":
        m = re.match(r"\s*/\*\*(.*?)\*/[ \t]*\n?", text, re.S)
        if not m:
            return {}, text
        lines = [re.sub(r"^\s*\* ?", "", l) for l in m.group(1).splitlines()]
        return parse_fields(lines), text[m.end():]
    prefix = {".typ": "//", ".vim": '"'}.get(ext, "#")
    lines = text.splitlines(keepends=True)
    head = []
    while lines and lines[0].startswith(prefix) and not lines[0].startswith("#!"):
        head.append(lines.pop(0)[len(prefix):])
    return parse_fields(head), "".join(lines)


def strip_c_comments(s):
    out, i, n = [], 0, len(s)
    while i < n:
        if s.startswith("//", i):
            j = s.find("\n", i)
            i = n if j < 0 else j
            out.append(" ")
        elif s.startswith("/*", i):
            j = s.find("*/", i + 2)
            i = n if j < 0 else j + 2
            out.append(" ")
        elif s[i] in "\"'" and not (s[i] == "'" and i > 0 and s[i - 1].isalnum()):
            q, j = s[i], i + 1
            while j < n and s[j] != q:
                j += 2 if s[j] == "\\" else 1
            out.append(s[i:j + 1])
            i = j + 1
        else:
            out.append(s[i])
            i += 1
    return "".join(out)


def code_hash(code, marks=()):
    """What hash.sh prints for the code typed with //! after each marked line:
    `grep -v //! | cpp -dD -P -fpreprocessed | grep -v '^#define __' | tr -d '[:space:]' | md5sum | cut -c-6`."""
    code = "\n".join(l for i, l in enumerate(code.split("\n"), 1) if i not in marks)
    flat = re.sub(r"\s", "", strip_c_comments(code))
    if not flat:
        return ""
    return hashlib.md5(flat.encode()).hexdigest()[:6]


def take_marks(code):
    """Strip trailing //! markers; return (code, 1-based marked line numbers)."""
    lines, marks = [], []
    for i, line in enumerate(code.split("\n"), 1):
        if MARK_RE.search(line):
            line = MARK_RE.sub("", line)
            marks.append(i)
        lines.append(line)
    return "\n".join(lines), marks


def load():
    cfg = tomllib.loads((ROOT / "notebook.toml").read_text())
    max_cols = cfg.get("layout", {}).get("max_cols", 60)
    chapters, warnings = [], []
    for ci, ch in enumerate(cfg["chapter"]):
        items = []
        for f in ch["files"]:
            follow = f.startswith("+")  # keep right after the previous file
            f = f.lstrip("+")
            path = ROOT / "snippets" / ch["dir"] / f
            meta, code = split_header(path, path.read_text())
            lang = LANG.get(path.suffix, "")
            needs = [x.strip() for x in meta.get("needs", "").split(",") if x.strip()]
            uses, uses_needs = "", []
            if lang == "cpp":
                code = re.sub(r"^\s*#pragma once[ \t]*\n", "", code, flags=re.M)
                parts = USES_RE.split(code, maxsplit=1)
                if len(parts) == 2:
                    code, uses = parts
                needs += INCLUDE_RE.findall(code)
                uses_needs = INCLUDE_RE.findall(uses)  # needed only by the Uses block
                code, uses = INCLUDE_RE.sub("", code), INCLUDE_RE.sub("", uses)
            code, marks = take_marks(code.strip("\n"))
            uses, uses_marks = take_marks(uses.strip("\n"))
            item = {k: meta.get(k, "") for k in SHOWN}
            item.update(
                title=meta.get("name") or path.stem,
                file=f,
                chapter=ci,
                follow=follow,
                lang=lang,
                kind="typ" if lang == "typ" else "code",
                path=str(path.relative_to(ROOT)),
                code="" if lang == "typ" else code,
                marks=marks,
                uses=uses,
                uses_marks=uses_marks,
                hash=code_hash(code, marks) if lang == "cpp" else "",
                uses_hash=code_hash(uses, uses_marks) if lang == "cpp" else "",
                needs=", ".join(pathlib.Path(n).stem for n in needs),
                uses_needs=", ".join(pathlib.Path(n).stem for n in uses_needs),
            )
            if lang != "typ":
                for block in (code, uses):
                    for line in block.splitlines():
                        if len(line.expandtabs(2)) > max_cols:
                            warnings.append(f"{item['path']}: {len(line)} chars > {max_cols}: {line.strip()[:40]}")
            items.append(item)
        chapters.append({"name": ch["name"], "items": items})
    return cfg, chapters, warnings


def gxx():
    for c in ("g++-16", "g++-15", "g++-14", "g++-13", "g++"):
        if shutil.which(c):
            return c
    sys.exit("no g++ found")


def check(cfg):
    ok = True
    for ch in cfg["chapter"]:
        for f in ch["files"]:
            path = ROOT / "snippets" / ch["dir"] / f.lstrip("+")
            if LANG.get(path.suffix) != "cpp" or f == "template.cpp" or path.suffix == ".frag":
                continue
            # x86-only pragmas (avx2) cannot be checked on other machines
            if "#pragma GCC target" in path.read_text() and platform.machine() not in ("x86_64", "AMD64"):
                continue
            r = subprocess.run([gxx(), "-std=c++20", "-Wall", "-Wextra", "-fsyntax-only",
                                "-Wno-pragma-once-outside-header", "-Wno-sign-compare", "-Wno-psabi",
                                "-include", str(ROOT / "tests/common.h"), "-I", str(ROOT / "snippets"),
                                "-x", "c++", str(path)], text=True, capture_output=True)
            status = "ok" if r.returncode == 0 and not r.stderr else "FAIL" if r.returncode else "warn"
            ok &= r.returncode == 0
            if status != "ok":
                print(f"  {status:4} {ch['dir']}/{f}")
                print("\n".join("       " + l for l in r.stderr.strip().splitlines()[:12]))
    print("syntax check:", "all ok" if ok else "FAILED")
    return ok


def main():
    cfg, chapters, warnings = load()
    BUILD.mkdir(exist_ok=True)
    (BUILD / "data.json").write_text(json.dumps(chapters, indent=1))
    for w in warnings:
        print("warning:", w)
    if "--check" in sys.argv and not check(cfg):
        sys.exit(1)
    fonts = ["--font-path", str(ROOT / "fonts")] if (ROOT / "fonts").is_dir() else []
    have = subprocess.run(["typst", "fonts", *fonts], capture_output=True, text=True).stdout.splitlines()
    sans = next((f for f in ("Helvetica Neue", "Helvetica", "DejaVu Sans", "Liberation Sans") if f in have),
                "Libertinus Serif")
    fonts += ["--input", f"sans={sans}"]
    subprocess.run(["typst", "compile", *fonts, "notebook.typ", "notebook.pdf"], cwd=ROOT, check=True)
    q = subprocess.run(["typst", "query", *fonts, "notebook.typ", "<stats>", "--field", "value", "--one"],
                       cwd=ROOT, check=True, capture_output=True, text=True)
    st = json.loads(q.stdout)
    print(f"notebook.pdf: {st['pages']} pages, {st['columns']} columns, "
          f"average column fill {st['fill']:.0%}"
          + (f", lowest {st['min_fill']:.0%} (column {st['min_col']})" if st['columns'] > 1 else ""))
    if st["pages"] > 25:
        print(f"warning: {st['pages']} pages, the limit is 25")
    if st["overflow"]:
        print(f"error: column(s) {', '.join(st['overflow'])} overflow and get clipped; "
              "add blank lines (split points) to the snippet or shorten it")
        if "--check" in sys.argv:
            sys.exit(1)
    if "--png" in sys.argv:
        for old in BUILD.glob("page-*.png"):
            old.unlink()
        subprocess.run(["typst", "compile", *fonts, "notebook.typ", "build/page-{p}.png", "--ppi", "150"],
                       cwd=ROOT, check=True)


if __name__ == "__main__":
    main()
