// Name: Expected value
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Linearity][$E[X + Y] = E[X] + E[Y]$ always, even when $X$ and $Y$
depend on each other. Write the quantity as a sum of indicators (one
per element, pair, edge, ...): $E = sum P("event")$. Random
permutation: $1$ fixed point, $n(n-1)\/4$ inversions, $H_n$ prefix
maxima. Keep each vertex of a tree with probability $p$: components
$= n p - (n - 1) p^2$ (kept vertices minus kept edges). Squares:
$E[(sum_i I_i)^2] = sum_(i, j) P(I_i "and" I_j)$.]

#t[Tail sum][For $X in {0, 1, 2, dots}$: $E[X] = sum_(k >= 1) P(X >= k)$.
Maximum of independent values: $P(max <= v) = product_i P(X_i <= v)$,
then the tail sum.]

#t[Waiting][Success with probability $p$ per try: $1\/p$ tries on
average. Stages with probabilities $p_1, p_2, dots$ one after another:
$sum 1\/p_i$; coupon collector: $n H_n$. Fair $plus.minus 1$ walk from
$a$ inside $[0, N]$: reaches $N$ before $0$ with probability $a\/N$,
after $a(N - a)$ steps on average.]

#t[DP backwards][$E_s$ = expected remaining cost from state $s$:
terminal states have $E = 0$, and
$E_s = c_s + sum_t P(s -> t) E_t$, computed in reverse topological
order. A self-loop with probability $q$:
$E_s = (c_s + sum_(t != s) P(s -> t) E_t) \/ (1 - q)$. Other cycles: a
linear system (Gauss, $O(n^3)$). On a tree or a line, write
$E_v = A_v E_"parent" + B_v$ bottom-up, then go top-down.]

#t[DP forwards][$P_s$ = probability of reaching state $s$, pushed
from the start; the answer is $sum_s P_s dot "value"_s$. Use it when the
stopping rule depends on the past or values are collected on the
way.]

#t[Modulo a prime][An answer $P\/Q$ is printed as $P Q^(-1) mod p$:
run the whole computation in `mint`; probability $1\/k$ is
`mint(k).inv()`. Linearity and the DPs work unchanged.]

#t[Symmetry][In a random permutation, $i$ comes before $j$ with
probability $1\/2$; a given element is the largest of a random
$k$-subset with probability $1\/k$. For a quantity that is the same
for every position, compute one position and multiply.]
