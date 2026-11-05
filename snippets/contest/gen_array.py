# Name: Generator: array
# Description: Every generator is called as `python3 FILE SEED`
#   and then optional maxima that replace the defaults (small, for
#   stress tests). Here: $n in [1, N]$, then $n$ values in $[1, V]$.
# Usage: python3 gen_array.py 7          # n <= 6, values <= 10
#   python3 gen_array.py 1 200000 1000000000 > big
import sys, random as rd
A = sys.argv + [None] * 3
rd.seed(int(A[1]))
N, V = int(A[2] or 6), int(A[3] or 10)
n = rd.randint(1, N)
print(n)
print(*(rd.randint(1, V) for _ in range(n)))
