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

#t[Matrix-tree][The number of spanning trees is the determinant of the
Laplacian $L = D - A$ with any one row and column removed. Directed,
rooted at $r$ (edges away from $r$): use in-degrees, remove row and column $r$.]

#t[LGV][Counts families of paths that do not touch. Take a DAG with
sources $a_1, dots, a_k$ and sinks $b_1, dots, b_k$, and let
$M_(i j)$ be the number of paths $a_i -> b_j$ (or the sum over those
paths of the product of edge weights). Then $det M$ equals the sum, over
all families of $k$ pairwise vertex-disjoint paths $a_i -> b_(sigma(i))$, of
$"sign"(sigma)$. Reason: in a family where two paths share a vertex, swap
their tails after the first shared vertex; this pairs such families with
opposite signs, so they cancel. Use: when the geometry forces
$sigma = "id"$, $det M$ is exactly the number of disjoint families. This holds
on a grid when sources and sinks lie on the border in the same order.
For example, for $k = 2$ the count is $M_(1 1) M_(2 2) - M_(1 2) M_(2 1)$; on a grid
$M_(i j) = binom(Delta x + Delta y, Delta x)$. Two paths $(0,0) -> (n,m)$
that meet only at the ends: sources $(0,1), (1,0)$, sinks
$(n-1,m), (n,m-1)$. Compute $det$ modulo a prime with `det`.]

#t[Sprague–Grundy][A position's Grundy value is the mex of the values of
the positions reachable in one move. A sum of independent games is lost
for the player to move iff the XOR of the Grundy values is 0. Nim: a
pile of size $x$ has value $x$.]

#t[Erdős–Gallai][$d_1 >= dots >= d_n$ is the degree sequence of a simple
graph iff the sum is even and for every $k$:
$sum_(i<=k) d_i <= k(k-1) + sum_(i>k) min(d_i, k)$.]
