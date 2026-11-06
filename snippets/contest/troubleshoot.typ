// Name: Troubleshooting
#set list(spacing: 2.6pt, indent: 0pt, body-indent: 3pt, marker: [–])
#let hd(t) = text(font: sys.inputs.at("sans", default: "Helvetica Neue"), weight: "bold", size: 6.5pt, t)
#grid(columns: (1fr, 1fr), column-gutter: 8pt, row-gutter: 5pt,
[
  #hd[Before submitting]
  - Stress test against a brute force.
  - Max-size input: time and memory.
  - Edge cases: $n = 0, 1$, all equal, sorted.
  - `int` overflow? Clear globals between tests?
  - Output format, precision, trailing spaces.
], [
  #hd[Wrong answer]
  - Reread the statement. Print debug output.
  - Overflow, uninitialized or shadowed variables.
  - Off-by-one, `<` vs `<=`, 0/1-indexing.
  - Equal elements, ties, special cases.
  - Precision: compare with eps, avoid `==`.
], [
  #hd[Runtime error]
  - Index out of range: compile with `-fsanitize`.
  - Stack overflow from deep recursion.
  - Division by zero, `sqrt` or `log` of a negative.
  - Iterators invalidated by `push_back`/`erase`.
  - `-D_GLIBCXX_DEBUG`: checked `[]` and iterators.
  - Is it a crash? First line of `main`: \
    `signal(SIGSEGV, [](int) { _Exit(0); });` \
    turns it into WA (also `SIGFPE`, `SIGABRT`).
  - NaN or $plus.minus infinity$? `feenableexcept(FE_INVALID |` \
    `FE_DIVBYZERO | FE_OVERFLOW)` crashes at the first one
    (Linux only).
], [
  #hd[Time or memory limit]
  - Infinite loop? Complexity really ok?
  - `endl` flushes: use `'\n'`. Copying big vectors.
  - `map` → sorted vector or `unordered_map`.
  - Recursion → iteration. Precompute more.
])
