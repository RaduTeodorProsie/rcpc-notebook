// Name: Randomization
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Set hashing][Give every value $v$ a random 64-bit $r_v$. A multiset
hashes to $sum r_v$ (mod $2^64$, just let `ull` overflow), a set with
parities to $xor.big r_v$ (XOR). Two different multisets collide
with probability $2^(-64)$, so even $10^12$ comparisons are safe. With
prefix hashes, a subarray of length $k$ is a permutation of $1..k$ iff its sum hash
equals $r_1 + dots + r_k$, and every value appears an even number of
times iff two prefix XORs are equal. Trees up to isomorphism: hash a
vertex as a random function of the sorted (or summed, hashed) hashes
of its children.]

#t[Shuffling][Shuffle the input when an algorithm is fast on average
but slow on bad orders: treap priorities, quicksort pivots, incremental
constructions (minimum enclosing circle in expected $O(n)$), inserting
points into a hull or grid. Rotate by a random angle to avoid vertical
lines or equal $x$.]

#t[Schwartz–Zippel][A nonzero polynomial of degree $d$ vanishes at a
random point mod $p$ with probability $<= d\/p$. Check $A B = C$ by
comparing $A (B v)$ with $C v$ for a random vector $v$, in $O(n^2)$.
Perfect matching in a general graph: the Tutte matrix (for each edge,
$x_(u v) = r$ and $x_(v u) = -r$, $r$ random) has a nonzero
determinant iff a perfect matching exists (w.h.p.); its rank is twice
the maximum matching.]

#t[Sampling][An element occurring more than $n\/k$ times in a range is
hit by a random index with probability $> 1\/k$: try about $20 k$
random positions and count each candidate (e.g. with sorted position
lists and binary search). Estimating: average many random trials.]

#t[Colour coding][Find a simple path (or tree) on $k$ vertices: colour
the vertices randomly with $k$ colours and look for a path with all
colours distinct, by a DP over (vertex, set of colours), $O(2^k m)$. A
fixed solution gets distinct colours with probability
$k!\/k^k >= e^(-k)$; repeat about $e^k$ times.]

#t[Birthday][Among about $sqrt(N)$ random values from $N$ there are
two equal ones: random search for a collision (equal hashes, equal
sums) needs about $sqrt(N)$ tries. With $n$ items and a $64$-bit hash,
a collision is likely only for $n approx 2^32$.]

#t[Anti-hacks][`unordered_map` with a fixed hash can be attacked:
hash keys with splitmix64 of $x$ plus a random constant. String hash:
random base modulo $2^61 - 1$ (`hashing.h`). Seed `mt19937_64` with
the clock.]

#t[Heuristics][Running out of ideas on an optimisation problem with a
loose checker: random restarts, hill climbing or simulated annealing
until a time limit (`clock()`).]
