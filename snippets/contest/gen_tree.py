# Name: Generator: tree
# Description: `SEED [N] [W]`: $n$, then $n - 1$ edges `u v`
#   (1-indexed) with a weight in $[1, W]$ if $W > 0$. Vertex $i$
#   hangs from a random earlier one; labels and edge order are
#   shuffled. Deep trees: parent from $[i - 3, i)$ instead.
import sys, random as rd
A = sys.argv + [None] * 3
rd.seed(int(A[1]))
N, W = int(A[2] or 6), int(A[3] or 0)
R = rd.randint
n = R(1, N)
p = list(range(1, n + 1))
rd.shuffle(p)
es = [[p[R(0, i - 1)], p[i]] for i in range(1, n)]
rd.shuffle(es)
print(n)
for e in es:
  rd.shuffle(e)
  print(*e, *([R(1, W)] if W else []))
