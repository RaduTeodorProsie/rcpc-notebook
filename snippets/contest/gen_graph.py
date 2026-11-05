# Name: Generator: graph
# Description: `SEED [N] [M] [W] [C]`: $n$ and $m$ ($m <= M$, or $n - 1$ if
#   $C = 1$ needs more), then $m$
#   edges `u v` (1-indexed, no loops or multi-edges) with a weight
#   in $[1, W]$ if $W > 0$. $C = 1$: connected (a random spanning
#   tree first). Directed: take pairs $(u, v)$ with $u != v$ instead.
import sys, random as rd
A = sys.argv + [None] * 5
rd.seed(int(A[1]))
N, M = int(A[2] or 6), int(A[3] or 8)
W, C = int(A[4] or 0), int(A[5] or 0)
R = rd.randint
n = R(1, N)
p = list(range(1, n + 1))
rd.shuffle(p)
es = {tuple(sorted((p[R(0, i - 1)], p[i])))
      for i in range(1, n)} if C else set()
rest = [(u, v) for u in range(1, n + 1)
        for v in range(u + 1, n + 1) if (u, v) not in es]
k = R(0, max(0, min(len(rest), M - len(es))))
es = list(es) + rd.sample(rest, k)
rd.shuffle(es)
print(n, len(es))
for u, v in es:
  print(*rd.sample((u, v), 2), *([R(1, W)] if W else []))
