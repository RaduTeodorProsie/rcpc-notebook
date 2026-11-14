// Name: Combinatorics
#import "/snippets/sheet.typ": sec
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  sec[Counting],
  [Vandermonde], [$sum_k binom(m, k) binom(n, r-k) = binom(m+n, r)$],
  [Hockey stick], [$sum_(i=r)^n binom(i, r) = binom(n+1, r+1)$],
  [Binomial \ inversion], [$f(n) = sum_k binom(n, k) g(k) <==> g(n) = sum_k (-1)^(n-k) binom(n, k) f(k)$. \ Exactly $k$ of $n$ properties: let $F(j)$ = sum over the sets $T$ of $j$ properties of the number of objects with all of $T$ (and maybe more); then exactly $k$: $sum_(j>=k) (-1)^(j-k) binom(j, k) F(j)$],
  [Stars, bars], [solutions of $x_1 + dots + x_k = n$ with $x_i >= 0$: $binom(n+k-1, k-1)$],
  [Catalan $C_n$], [balanced bracket strings with $n$ pairs (also binary trees with $n$ nodes, triangulations of an $(n+2)$-gon): $C_n = binom(2n, n)\/(n+1)$, $C_(n+1) = sum_i C_i C_(n-i)$],
  [Reflection], [paths of $a$ up-steps and $b <= a$ down-steps that never go below the start: $binom(a+b, b) - binom(a+b, b-1)$ (flip a bad path before its first visit to $-1$: it becomes any path with $b - 1$ down-steps). Above the start after every step (ballot): $(a-b)/(a+b) binom(a+b, a)$],
  [Stirling 1 \ $c(n,k)$], [permutations of $n$ elements with exactly $k$ cycles. Element $n$ is a cycle alone, or is inserted right after one of the other $n - 1$: $c(n,k) = c(n-1,k-1) + (n-1) c(n-1,k)$. Signed: $s(n,k) = (-1)^(n-k) c(n,k)$],
  [Stirling 2 \ $S(n,k)$], [ways to split $n$ labelled items into $k$ non-empty groups, where the groups have no names or order ({1,2},{3} is the same as {3},{1,2}). Item $n$ is a group alone, or joins one of the $k$ groups of a split of the rest: $S(n,k) = S(n-1,k-1) + k S(n-1,k)$. \ Closed form: give the groups names $1..k$; that gives $k! S(n,k)$ onto maps (every name used). Count maps $n -> k$ that miss a chosen set of $i$ names, $(k-i)^n$, and use incl.–excl. over that set: $k! S(n,k) = sum_(i=0)^k (-1)^i binom(k,i)(k-i)^n$. \ Falling factorials: $x^n = sum_k S(n,k) x(x-1) dots.c (x-k+1)$],
  [Eulerian \ $A(n,k)$], [permutations of $n$ with exactly $k$ ascents ($pi_i < pi_(i+1)$). Insert $n$ into a permutation of $n - 1$: in an ascent or at the front keeps the count, elsewhere adds one: $A(n,k) = (k+1) A(n-1,k) + (n-k) A(n-1,k-1)$. $A(n,k) = sum_(j=0)^k (-1)^j binom(n+1, j)(k+1-j)^n$, #h(2pt) $sum_k A(n,k) binom(x+k, n) = x^n$],
  [Bell $B_n$], [ways to split $n$ labelled items into any number of non-empty groups: $B_n = sum_k S(n,k)$, $B_(n+1) = sum_k binom(n, k) B_k$],
  [Derangements], [permutations without fixed points: $D_n = (n-1)(D_(n-1) + D_(n-2)) = n! sum_(i=0)^n (-1)^i \/ i!$],
  [Partitions $p(n)$], [ways to write $n$ as an unordered sum of positive integers; $p(0) = 1$, \
    $p(n) = p(n-1) + p(n-2) - p(n-5) - p(n-7) + p(n-12) + p(n-15) - dots$: \
    subtract the pentagonal numbers $1, 2, 5, 7, 12, 15, 22, 26, dots$ ($k(3k-1)\/2$ for $k = 1, -1, 2, -2, dots$), signs in pairs $+ + - - + + dots$, stop when one exceeds $n$],
  [Incl.–excl.], [$|union.big A_i| = sum_(S != emptyset) (-1)^(|S|+1) |inter.big_(i in S) A_i|$],
)
