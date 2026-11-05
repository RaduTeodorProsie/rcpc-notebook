# Name: Generator: string
# Description: `SEED [N] [ALPHABET]`: length in $[1, N]$, letters
#   from the alphabet (default `ab`: few letters give many repeats,
#   borders and palindromes).
import sys, random as rd
A = sys.argv + [None] * 3
rd.seed(int(A[1]))
N, al = int(A[2] or 8), A[3] or "ab"
n = rd.randint(1, N)
print("".join(rd.choice(al) for _ in range(n)))
