// Name: Theorems in words
#set par(justify: true, spacing: 4.2pt)
#let t(name, body) = [#text(font: sys.inputs.at("sans", default: "Helvetica Neue"), weight: "bold", size: 6.5pt, name) #h(2pt) #body]
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

#t[LGV][In a DAG with sources $a_i$ and sinks $b_i$, $det(M)$ with
$M_(i j) = $ number of paths $a_i -> b_j$ counts tuples of vertex-disjoint
paths, signed by the permutation they realise. If only $a_i -> b_i$ can be
disjoint (e.g. planar, ordered endpoints), it is the exact count.]

#t[Sprague–Grundy][A position's Grundy value is the mex of the values of
the positions reachable in one move. A sum of independent games is lost
for the player to move iff the XOR of the Grundy values is 0. Nim: a
pile of size $x$ has value $x$.]

#t[Erdős–Gallai][$d_1 >= dots >= d_n$ is the degree sequence of a simple
graph iff the sum is even and for every $k$:
$sum_(i<=k) d_i <= k(k-1) + sum_(i>k) min(d_i, k)$.]
