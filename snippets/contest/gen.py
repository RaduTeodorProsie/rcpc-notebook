# Name: Random generator
# Description: `python3 gen.py SEED KIND key=value ...`. Kinds:
#   `array`, `perm`, `string`, `tree`, `graph`, `conn` (connected
#   graph), `queries`. Keys: `n` max size, `v` max value, `m`
#   max edges, `w` max weight (0 = unweighted), `q` queries,
#   `a` alphabet, `one=0` for 0-indexed output. Edit the
#   `print`s to match the input format.
import sys, random as rd
A = sys.argv
rd.seed(int(A[1]))
kind = A[2] if len(A) > 2 else "array"
o = dict(x.split("=") for x in A[3:])
g = lambda k, d: int(o.get(k, d))
R = rd.randint
n, V, W = R(1, g("n", 8)), g("v", 10), g("w", 0)
one = g("one", 1)

def out(es, head):  # random labels and order, opt. weights
  p = list(range(one, n + one))
  rd.shuffle(p), rd.shuffle(es)
  print(*head)
  for u, v in es:
    print(p[u], p[v], *([R(1, W)] if W else []))

if kind == "array":
  print(n)
  print(*(R(1, V) for _ in range(n)))
elif kind == "perm":
  p = list(range(1, n + 1))
  rd.shuffle(p)
  print(n)
  print(*p)
elif kind == "string":
  al = o.get("a", "ab")
  print("".join(rd.choice(al) for _ in range(n)))
elif kind in ("tree", "conn"):
  es = [(R(0, i - 1), i) for i in range(1, n)]  # parent < i
  if kind == "conn" and n > 1:
    es += [tuple(rd.sample(range(n), 2))
           for _ in range(R(0, g("m", n)))]
  out(es, [n] if kind == "tree" else [n, len(es)])
elif kind == "graph":
  es = [(u, v) for u in range(n) for v in range(u + 1, n)]
  es = rd.sample(es, R(0, min(len(es), g("m", 2 * n))))
  out(es, [n, len(es)])
elif kind == "queries":
  q = g("q", 5)
  print(n, q)
  print(*(R(1, V) for _ in range(n)))
  for _ in range(q):
    l = R(one, n - 1 + one)
    print(R(1, 2), l, R(l, n - 1 + one))  # type, l, r
else:
  sys.exit("unknown kind " + kind)
