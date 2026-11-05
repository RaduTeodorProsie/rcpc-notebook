// Name: DP techniques
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Which optimisation][
$d p_i = min_j (d p_j + b_j a_i + c_j)$: line $b_j x + d p_j + c_j$ queried
at $a_i$: CHT (`cht.h`), or Li Chao; a deque if slopes and queries are
monotone. \
$d p_(k,i) = min_(j < i) (d p_(k-1,j) + C(j, i))$ with $C$ satisfying the
quadrangle inequality: divide and conquer (`dcopt.h`),
$O(k n log n)$. \
$d p_(l,r) = min_(l < m < r) (d p_(l,m) + d p_(m,r)) + C(l, r)$: Knuth
(`knuth.h`), $O(n^2)$. \
Exactly $k$ groups, cost convex in $k$: Aliens (`aliens.h`), drops
the $k$ dimension. \
$d p$ as a function of a value, with $min$, shifts and $|x - a|$: slope
trick (`slope.h`). \
Quadrangle inequality:
$C(a, c) + C(b, d) <= C(a, d) + C(b, c)$ for $a <= b <= c <= d$; holds
for $C = f("sum of the segment")$ with $f$ convex and values $>= 0$.]

#t[Swap value and state][If the answer is small but a dimension is
large, use $d p_(i, "answer")$ = best value of the large dimension,
e.g. knapsack with huge weights: min weight for each total value.]

#t[Components][Counting permutations with conditions on neighbours:
insert values in increasing order, the state being the number of
blocks of the final order built so far. A new value starts a new
block, sticks to one end of a block, or glues two blocks together;
the condition decides which moves are allowed and with how many
ways.]

#t[Broken profile][Tilings of an $n times m$ grid with small $m$: go
cell by cell, the state is the mask of the $m$ cells on the frontier
(already covered or not), $O(n m 2^m)$.]

#t[Digits][Count $x <= N$ with a property: go over the digits of $N$
from the top, with a flag "still equal to $N$'s prefix" (and "only
leading zeros so far" if they matter); answer for $[L, R]$ is
$f(R) - f(L - 1)$.]

#t[Trees][Rerooting: compute subtree values bottom-up, then the value
"from the parent's side" top-down using prefix and suffix
combinations of the children; all roots in $O(n)$. Merging children
with sizes capped at $k$: $O(n k)$ total, not $O(n k^2)$.]

#t[Knapsack][0/1: loop capacity downwards. Count $c_i$ copies:
binary splitting into $1, 2, 4, dots$ copies. Counting ways: an item
can be removed by running its update backwards (subtract). Bitset for
feasibility.]

#t[Subsets][$d p_("mask", v)$ for paths through a set (TSP,
$O(2^n n^2)$); all submasks of all masks in $O(3^n)$; sums over
subsets: `subsets.h`.]
