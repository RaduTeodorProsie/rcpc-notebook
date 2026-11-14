// Name: Theorems: graphs
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Hall][A bipartite graph has a matching covering every left vertex
iff every set $S$ of left vertices has at least $|S|$ neighbours. In
general: max matching $= |L| - max_(S subset.eq L) (|S| - |N(S)|)$.]

#t[König][In a bipartite graph: max matching $=$ min vertex cover, and
max independent set $= V -$ max matching (the complement of the cover);
both sets from `vertexCover`. Min _weight_ vertex cover $=$ min cut
with $s -> u$ of capacity $w_u$ on the left, $v -> t$ of capacity $w_v$
on the right and the graph's edges $infinity$. In any graph without
isolated vertices: min edge cover $= V -$ max matching.]

#t[Dilworth][In a partial order, the largest antichain $=$ the fewest
chains that cover all elements $= n -$ max matching between left
copies and right copies, with an edge $u_L - v_R$ for every pair
$u < v$ (in a DAG: every $v$ reachable from $u$, the transitive
closure). The antichain: all $v$ with neither $v_L$ nor $v_R$ in the
min vertex cover. With only the DAG's own edges, $n -$ max matching is
the fewest vertex-disjoint paths covering the DAG. Dually (Mirsky):
longest chain $=$ fewest antichains (group $v$ by the longest chain
ending at $v$). Sequences: fewest non-increasing subsequences that
cover $a$ $=$ longest strictly increasing subsequence.]

#t[Closure][Choose vertices of maximum total weight, where choosing
$u$ forces $v$ for every edge $u -> v$: (sum of the positive weights)
$-$ min cut, with $s -> v$ of capacity $w_v$ if $w_v > 0$, $v -> t$ of
capacity $-w_v$ if $w_v < 0$ and the graph's edges $infinity$. The
chosen set is the $s$ side (`minCut`).]

#t[Matrix-tree][$L_(v v)$ = total weight of the edges at $v$,
$L_(u v) = -$(total weight of the edges $u v$); unweighted: weight $1$
each, so parallel edges add up; loops are dropped. Delete row $r$ and
column $r$, any $r$: $det$ = sum over the spanning trees of the product
of their edge weights, so the number of spanning trees if unweighted
(`det` on `mint`). \
_Directed, root $r$:_ $L_(u v) = -w(u -> v)$. $L_(v v)$ = weight
_entering_ $v$ counts the trees with all edges pointing away from $r$;
$L_(v v)$ = weight _leaving_ $v$, those pointing towards $r$. Delete
row and column $r$. \
_Exactly $k$ special edges:_ give them weight $x$, take $det$ at
$x = 0..n-1$, then `interp`: coefficient of $x^k$. \
_Euler circuits of a directed graph (BEST):_ (trees towards any $r$)
$dot product_v (op("out")(v) - 1)!$. \
_Closed forms:_ $K_n$: $n^(n-2)$. $K_(a,b)$: $a^(b-1) b^(a-1)$. Trees
with degrees $d_i$: $(n-2)! \/ product (d_i - 1)!$. Ways to join
components of sizes $s_1..s_k$ into one tree:
$s_1 dots.c s_k dot n^(k-2)$.]

#t[LGV][DAG (often a grid), sources $a_1..a_k$, sinks $b_1..b_k$,
$M_(i j)$ = number of paths $a_i -> b_j$ (weighted: sum of the products
of edge weights). Then $det M = sum_sigma "sign"(sigma) dot$(number of
$k$-tuples of paths $a_i -> b_(sigma(i))$, no two sharing a vertex). \
_Counting:_ if for all $i < j$ and $k < l$ every path $a_i -> b_l$
meets every path $a_j -> b_k$, only $sigma = "id"$ is left and $det M$
(`det`) is the number of vertex-disjoint tuples joining $a_i$ to $b_i$.
On a grid: sources and sinks in the same order along the border, and
$M_(i j) = binom(Delta x + Delta y, Delta x)$ ($0$ if $Delta x$ or
$Delta y$ is negative). \
_Paths may touch but not cross:_ shift source and sink $i$ by
$(i, -i)$ ($i$ grows towards the lower right), then count disjoint
ones. \
_Example:_ two paths $(0,0) -> (n,m)$ meeting only at the ends =
disjoint paths from $(0,1), (1,0)$ to $(n-1,m), (n,m-1)$:
$M_(1 1) M_(2 2) - M_(1 2) M_(2 1)$.]

#t[Degree sequences][_Erdős–Gallai:_ $d_1 >= dots >= d_n$ is the
degree sequence of a simple graph iff the sum is even and for every
$k$: $sum_(i<=k) d_i <= k(k-1) + sum_(i>k) min(d_i, k)$. To build one
(Havel–Hakimi): join the vertex of largest remaining degree $d$ to the
next $d$ largest; repeat. \
_Bipartite (Gale–Ryser):_ left degrees $a_1 >= dots >= a_n$, right
degrees $b_j$: iff $sum a_i = sum b_j$ and for every $k$:
$sum_(i<=k) a_i <= sum_j min(b_j, k)$. \
_Tree:_ iff all $d_i >= 1$ and $sum d_i = 2(n-1)$. \
_Tournament (Landau):_ scores $s_1 <= dots <= s_n$: iff
$sum_(i<=k) s_i >= binom(k, 2)$ for every $k$, with equality at
$k = n$.]
