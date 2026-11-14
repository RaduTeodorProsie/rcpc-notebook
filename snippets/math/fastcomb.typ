// Name: Combinatorics: fast computation
#import "/snippets/sheet.typ": sec
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  [Small tables], [all $S$, $c$, $binom(n, k)$ for $n, k <= N$: fill the recurrences row by row, $O(N^2)$; $binom(n, k)$ for one query: precompute $n!$ and $1\/n!$ in $O(N)$],
  [$S(n, 0..n)$], [one row in $O(n log n)$. Divide the closed form by $k!$ and write $binom(k,i)\/k! = 1\/(i!(k-i)!)$: $S(n,k) = sum_(i+j=k) (-1)^i \/ i! dot j^n \/ j!$. That is the product of the polynomials with coefficients $a_i = (-1)^i\/i!$ and $b_j = j^n\/j!$, coefficient $k$: one NTT, `stirling2`],
  [$c(n, 0..n)$], [one row in $O(n log^2 n)$: $sum_k c(n,k) x^k = x(x+1) dots (x+n-1)$. Multiply the $n$ factors as a balanced tree: split them into two halves, multiply each half recursively, then the two results with one NTT: `stirling1`],
  [$B_n$], [one $n$: sum the row $S(n, dot)$, $O(n log n)$. All $B_0..B_N$: the Bell triangle, $O(N^2)$: row $0$ is $1$; each row starts with the last entry of the row above, and each next entry is its left neighbour plus the entry above that neighbour. The first entry of row $n$ is $B_n$. Mod a small prime $p$: $B_(n+p) equiv B_n + B_(n+1)$],
  [Power series], [in $O(n^2)$, coefficient by coefficient. $g = e^f$ ($f_0 = 0$): $g_0 = 1$, $n g_n = sum_(k=1)^n k f_k g_(n-k)$. \ $g = ln f$ ($f_0 = 1$): $n g_n = n f_n - sum_(k=1)^(n-1) k g_k f_(n-k)$. \ $g = f^c$ ($f_0 = 1$, any $c$): $g_0 = 1$, $n g_n = sum_(k=1)^n (c k - n + k) f_k g_(n-k)$],
  [$p(0..n)$], [$O(n sqrt(n))$: fill $p(0), p(1), dots$ in order with the recurrence above, $O(sqrt(n))$ terms each. Partitions into parts $<= m$: knapsack $O(n m)$],
)
