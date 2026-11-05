# RCPC team notebook

A 25-page ICPC team reference document. Snippets are KACTL-style
files under `snippets/`; the PDF is laid out with Typst so that **no
snippet is ever split across a column or a page**.

## Commands

| Command | What it does |
|---|---|
| `python3 build.py` | build `notebook.pdf` (needs `typst`) |
| `python3 build.py --check --png` | also syntax-check every C++ snippet and render `build/page-N.png` |
| `python3 test.py` | run every test with ASan/UBSan (needs `g++`) |
| `python3 test.py suffix lca` | only tests whose path matches |
| `python3 test.py --fast` | `-O2`, no sanitizers |
| `python3 test.py --coverage` | list `.h` snippets that no test includes |

## Writing a snippet

```cpp
/**
 * Name: Lazy segment tree
 * Description: Typst markup: $O(log n)$, `code`, ...
 * Time: $O(log n)$
 * Usage: verbatim text, may span lines
 */
#pragma once                 // hidden in the PDF
#include "point.h"           // hidden, printed as "Needs: point"
...code...                   // lines ending in //! are shaded: edit these
// --- uses ---
...short functions built on the code above, also tested...
```

- Keep code lines at most 60 characters (`build.py` warns otherwise).
- Add the file to its chapter in `notebook.toml`; the order there is the
  print order, except that the packer may swap a snippet with one of the
  next `layout.window` snippets to avoid gaps (`window = 1` forbids it).
- `.typ` files (formula sheets) are included as Typst content.
- The 6-character hash next to each title is
  `cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6`
  of the printed code, so a typed copy can be checked with `hash.sh`.

## Tests

One file per topic in `tests/<chapter>/`. A test `#include`s the
snippets it covers (paths relative to `snippets/`) and `testlib.h`, and
compares against a brute force on random inputs. It passes by exiting 0.
Every snippet sees the template prelude through `-include tests/common.h`.

## Layout

`notebook.typ` measures every snippet at the real column width, then
packs columns one at a time. Each column gets the next snippet plus the
subset of the next few that fills it best, and a gap a snippet doesn't fit
is filled by a later one. A snippet taller than a whole column first moves
its Uses block to its own box, and only then is cut at a blank line.
Columns are labelled `1a`, `1b`, ... and the contents page points to them.

Fonts: JetBrains Mono NL is bundled in `fonts/` (OFL). Titles use
Helvetica Neue when available, DejaVu Sans otherwise.
