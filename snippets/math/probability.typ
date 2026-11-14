// Name: Probability and linear algebra
#import "/snippets/sheet.typ": sec
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  sec[Expectation],
  [Basics], [$E[X] = sum_(k>=1) P(X >= k)$ for $X in NN$. Linearity holds for dependent variables too. $"Var" X = E[X^2] - E[X]^2$; for independent $X, Y$: $"Var"(X + Y) = "Var" X + "Var" Y$, $E[X Y] = E[X] E[Y]$],
  [Min–max], [$max(S) = sum_(emptyset != T subset.eq S) (-1)^(|T|+1) min(T)$, and the same with $E$ on both sides: the time until all of $S$ have happened, from the times until the first of $T$],
  [Coupons], [drawing until all $n$ kinds are seen: $n H_n approx n ln n$ draws],
  sec[Distributions (mean, variance)],
  [Binomial], [successes in $n$ independent tries of probability $p$: $P(k) = binom(n, k) p^k (1-p)^(n-k)$; $n p$, $n p (1-p)$],
  [Geometric], [tries up to the first success: $P(k) = (1-p)^(k-1) p$, $k >= 1$; $1\/p$, $(1-p)\/p^2$],
  [Poisson], [events in unit time at rate $lambda$ (also $"Bin"(n, lambda\/n)$, $n$ large): $P(k) = e^(-lambda) lambda^k \/ k!$; $lambda$, $lambda$],
  [Uniform], [on $[a, b]$: $(a+b)\/2$, $(b-a)^2\/12$; on ${1, dots, n}$: $(n+1)\/2$, $(n^2-1)\/12$],
  [Exponential], [waiting time at rate $lambda$: density $lambda e^(-lambda x)$; $1\/lambda$, $1\/lambda^2$. Memoryless; the minimum of independent rates $lambda_i$ has rate $sum lambda_i$],
  [Normal], [independent normals add (means and variances add); a sum of many independent variables is about normal],
  sec[Markov chains],
  [Steps], [$P_(i j)$ = probability to move from $i$ to $j$. With the row vector $p$ of state probabilities, after $k$ steps: $p P^k$ (`matrix.h`)],
  [Stationary], [$pi P = pi$, $sum pi_i = 1$. If every state reaches every other: $pi_i = 1\/E["return time to" i]$. Random walk on a connected undirected graph: $pi_v = deg v\/(2m)$. If also aperiodic (gcd of cycle lengths $1$), $p P^k -> pi$ from any start],
  [Absorbing], [absorbing states have $P_(i i) = 1$. Probability of ending in absorbing $t$: $a_t = 1$, $a = 0$ at the other absorbing states, otherwise $a_i = sum_j P_(i j) a_j$. Expected steps: $e = 0$ when absorbed, otherwise $e_i = 1 + sum_j P_(i j) e_j$. Solve with `gauss`, or as a DP if the moves never return],
  sec[Linear algebra],
  [Rank one], [$det(A + u v^T) = (1 + v^T A^(-1) u) det A$, #h(2pt) $(A + u v^T)^(-1) = A^(-1) - (A^(-1) u v^T A^(-1))\/(1 + v^T A^(-1) u)$: update an inverse in $O(n^2)$],
  [Cramer], [$A x = b$: $x_i = det A_i \/ det A$, $A_i$ = $A$ with column $i$ replaced by $b$],
)
