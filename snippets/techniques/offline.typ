// Name: Offline and divide and conquer
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Sort and sweep][Sort the queries by a parameter and insert the
elements in the same order: "how many elements $<= x$ in $[l, r)$"
becomes Fenwick counts after inserting all elements $<= x$. Distinct
values in $[l, r)$: sort the queries by $r$, keep only the last
occurrence of every value marked in a Fenwick tree, count marks in
$[l, r)$.]

#t[Binary search the answer][When feasibility is monotone in the
answer ("can it be done with cost at most $x$?"); typical for
"minimise the maximum". Real numbers: a fixed $60$–$100$ iterations.
Many queries each needing their own binary search over the same
sequence of events: parallel binary search (`parallelbs.h`).]

#t[Reverse time][Only deletions: process the operations backwards, so
deletions become insertions (DSU). Insertions and deletions:
segment tree over time and a rollback DSU (`dyncon.h`).]

#t[CDQ][Each update affects only later queries (or pairs $i < j$ with
conditions on two more coordinates): `solve(l, r)` calls
`solve(l, m)` and `solve(m, r)`, then adds the effect of the updates
in $[l, m)$ on the queries in $[m, r)$, by sorting both halves on one
coordinate and sweeping a Fenwick tree on the other. Counting
$i < j$, $a_i < a_j$, $b_i < b_j$: $O(n log^2 n)$. The same splitting
turns an online insert-and-query problem into static subproblems.]

#t[Across the midpoint][Static queries on ranges: at each level of a
divide and conquer on the array, the queries containing the midpoint
$m$ are answered by combining a suffix of $[l, m)$ with a prefix of
$[m, r)$, precomputed in $O(r - l)$ (e.g. knapsack tables), the
others go down to one side. $O((n + q) log n)$ combines.]

#t[Small to large][Merge sets by inserting the smaller into the
larger: each element moves $O(log n)$ times. Subtree queries: keep the
set of the heavy child and insert the others ("DSU on tree"),
$O(n log n)$ insertions.]

#t[Flatten trees][Euler tour order makes subtrees ranges
$[t_"in", t_"out")$; path to the root can be handled by adding at $t_"in"$
and subtracting at $t_"out"$. Paths with HLD. "Reachable using edges of
weight $<= x$": a subtree of the Kruskal reconstruction tree (see
graph tricks).]
