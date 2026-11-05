// Name: How to stress test
#set par(justify: true, spacing: 4pt)
#set enum(spacing: 3pt, indent: 0pt, body-indent: 3pt)
#let b(t) = text(font: sys.inputs.at("sans", default: "Helvetica Neue"), weight: "bold", size: 6.5pt, t)
+ #b[Brute force.] Write `brute.cpp` with the same input and output
  as `sol.cpp`, but as simple as possible: try every subset,
  permutation or answer. Exponential is fine; being obviously
  correct is the point.
+ #b[Generator.] Copy the `gen_*.py` closest to the input format
  and edit its `print`s. Keep tests tiny (the defaults: $n <= 6$,
  values $<= 10$): small cases hit equal elements, $n = 1$, empty
  answers and ties far more often, and failures are readable.
+ #b[Run.] `./stress.sh "gen_array.py 6 5" 1000`. On a mismatch
  the failing input is printed; `python3 gen_array.py SEED 6 5`
  reproduces it. Lower the maxima until the counterexample is
  minimal, then debug by hand.
+ #b[Many correct answers.] Write `check.cpp` that reads `in`, `o1`
  (yours) and `o2` (brute): validate `o1` itself (e.g. the edges
  exist, the permutation is valid) and compare only the objective
  with `o2`. Exit with a nonzero code on failure.
+ #b[Speed.] Generate the maximum test once
  (`python3 gen_array.py 1 200000 1000000000 > big`, with
  `randint(1, N)` changed to `N` so $n$ is the maximum) and run
  `time ./sol < big`. Also try sorted, all-equal and path or star
  trees: random trees are shallow.
#v(4pt)
#b[Random structures.] Tree: parent of $i$ uniform in $[0, i)$, then
shuffle the labels; for deep trees take the parent from $[i-3, i)$.
Connected graph: tree plus random edges. DAG: edges $u -> v$ with
$u < v$ only, then relabel. Distinct values: `rd.sample(range(1, V + 1), n)`.
No duplicate edges: sample from the list of all pairs.
