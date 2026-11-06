// Name: Theorems in words
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Burnside][The number of objects up to symmetry is the _average number of
objects left unchanged_ by a symmetry: $1/(|G|) sum_g "fix"(g)$. Colourings
with $k$ colours: $"fix"(g) = k^("cycles of" g)$. Necklaces of length $n$
up to rotation: $1/n sum_(d|n) phi(d) k^(n\/d)$.]

#t[Pick][For a polygon with lattice-point vertices:
area $=$ interior points $+$ boundary points$\/2 - 1$. A segment
contains $gcd(|Delta x|, |Delta y|) + 1$ lattice points. Typical use:
interior points $= A - B\/2 + 1$ with $A$ from the shoelace formula.]

#t[Hall][A bipartite graph has a matching covering every left vertex
iff every set $S$ of left vertices has at least $|S|$ neighbours.]

#t[König][In a bipartite graph: max matching $=$ min vertex cover, and
max independent set $= V -$ max matching. In any graph without isolated
vertices: min edge cover $= V -$ max matching.]

#t[Dilworth][In a partial order, the largest antichain equals the fewest
chains that cover all elements. Fewest vertex-disjoint paths covering a
DAG $= n -$ max matching between left copies and right copies ($u -> v$
edge gives $u_L - v_R$); take the transitive closure first if paths may
share vertices. Dually (Mirsky): longest chain $=$ fewest antichains.]

#t[Matrix-tree][Number of spanning trees of a multigraph: $L_(v v)
= deg v$, $L_(u v) = -$(number of edges $u v$), loops ignored. Delete the
row and column of any one vertex; the answer is $det$ (`det`, mod a
prime). Edge weights instead of counts give the sum over spanning trees
of the product of weights. Directed trees with all edges pointing away
from $r$: $L_(v v)$ = in-degree, $L_(u v) = -$(edges $u -> v$); delete
row and column $r$.]

#t[LGV][Counts $k$-tuples of paths in a DAG (often a grid), from
sources $a_1, dots, a_k$ to sinks $b_1, dots, b_k$, that share no vertex.
Build $M_(i j)$ = number of paths $a_i -> b_j$ (grid:
$binom(Delta x + Delta y, Delta x)$); the answer is $det M$ (`det`). Valid
when disjoint paths can only join $a_i$ to $b_i$: on a grid, sources and
sinks on the border in the same order. In general
$det M = sum_sigma "sign"(sigma) dot$(disjoint tuples joining $a_i$ to
$b_(sigma(i))$). Example: two paths
$(0,0) -> (n,m)$ meeting only at the ends = disjoint paths from
$(0,1), (1,0)$ to $(n-1,m), (n,m-1)$: $M_(1 1) M_(2 2) - M_(1 2) M_(2 1)$.]

#t[Sprague–Grundy][A position's Grundy value is the mex of the values of
the positions reachable in one move. A sum of independent games is lost
for the player to move iff the XOR of the Grundy values is 0. Nim: a
pile of size $x$ has value $x$.]

#t[Erdős–Gallai][$d_1 >= dots >= d_n$ is the degree sequence of a simple
graph iff the sum is even and for every $k$:
$sum_(i<=k) d_i <= k(k-1) + sum_(i>k) min(d_i, k)$.]
