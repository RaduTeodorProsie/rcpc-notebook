# Name: Generator: array and queries
# Description: `SEED [N] [V] [Q]`. The array, then $q in [1, Q]$
#   lines: `1 l r` (query) or `2 l r x` (update), $1 <= l <= r <= n$.
import sys, random as rd
A = sys.argv + [None] * 4
rd.seed(int(A[1]))
N, V, Q = int(A[2] or 6), int(A[3] or 10), int(A[4] or 5)
R = rd.randint
n, q = R(1, N), R(1, Q)
print(n, q)
print(*(R(1, V) for _ in range(n)))
for _ in range(q):
  l, r = sorted((R(1, n), R(1, n)))
  if R(0, 1): print(1, l, r)
  else: print(2, l, r, R(1, V))
