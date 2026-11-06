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
| `python3 test.py --perf` | only the performance tests (`--no-perf` skips them) |
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
- `.typ` files (formula sheets, guides) are included as Typst content.
- `.sh`/`.py` files use `# Name:` header lines, `.vim` files `" Name:`.
- `.frag` files are C++ fragments printed like code but not compiled on
  their own (Mo's main loop, the lazy segment tree variants); tests
  `#include` them or swap them in (see below).
- The 6-character hash next to each title is
  `grep -v //! | cpp -dD -P -fpreprocessed | grep -v '^#define __' | tr -d '[:space:]' | md5sum | cut -c-6`
  of the printed code without its shaded (`//!`) lines, so a typed copy
  can be checked with `hash.sh` as long as the shaded lines end in `//!`
  there too (then they can be edited without changing the hash);
  `sh hash.sh sol.cpp 40 75` hashes only lines 40–75 of a bigger file,
  and in Vim `\h` on a visual selection does the same (`vimrc.vim`).

## Tests

One file per topic in `tests/<chapter>/`. A test `#include`s the
snippets it covers (paths relative to `snippets/`) and `testlib.h`, and
compares against a brute force on random inputs. It passes by exiting 0.
Every snippet sees the template prelude through `-include tests/common.h`.

A test starting with `// variants: data-structures/lazy.h data-structures/lazyvar.frag`
is compiled once per `// == name ==` block of the fragment, with the base
snippet's marked (`//!`) block replaced by that block; the test sees
`VARIANT` (0, 1, ...) and includes `VARIANT_FILE`.

Performance tests live in `tests/perf/` and cover the snippets whose
running time has no quick proof: amortized or randomized structures
(segment tree beats, link-cut tree, kinetic segment tree, directed MST,
dominator tree, Pollard rho, minimum enclosing circle, palindromic series
links) and algorithms far faster in practice than their bound (simplex,
including the Klee–Minty cube; Dinic, min-cost flow, Hopcroft–Karp,
blossom, Gomory–Hu). Each `PERF("name", ms) { ... }` block runs a
contest-sized input, often an adversarial one, and fails if it takes longer
than `ms` times `$PERF_SCALE` (default 1). They are built with `-O2` and no
sanitizers, and run one at a time after the other tests. They run locally
only, not in CI (shared runners time too unevenly). The budgets are about 3
times the times on an Apple Silicon laptop; on a slower machine run
`PERF_SCALE=2 python3 test.py`.

Stress testing during the contest: `snippets/contest/` has one
generator per input model (`gen_array.py`, `gen_queries.py`, `gen_string.py`,
`gen_tree.py`, `gen_graph.py`; `python3 gen_X.py SEED [maxima...]`) and
`stress.sh` (`./stress.sh "gen_tree.py 6" 1000`).

## Layout

`notebook.typ` measures every snippet at the real column width, then
packs columns one at a time. Each column gets the next snippet plus the
subset of the next few that fills it best, and a gap a snippet doesn't fit
is filled by a later one. A snippet taller than a whole column first moves
its Uses block to its own box, and only then is cut at a blank line. A
snippet with no blank line that is still too tall would run off the page,
so `build.py` reports any column that overflows (and `--check` fails).
Columns are labelled `1a`, `1b`, ... and the contents page points to them.

Fonts: JetBrains Mono NL is bundled in `fonts/` (OFL). Titles use
Helvetica Neue when available, DejaVu Sans otherwise.
