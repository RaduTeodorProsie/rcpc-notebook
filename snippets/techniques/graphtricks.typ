// Name: Graph tricks
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Shortest paths][Weights $0$ and $1$: 0-1 BFS with a deque (push
front for $0$, back for $1$). Extra state (coupons used, parity, time
mod $k$): Dijkstra on pairs (vertex, state). Many sources: all start
at distance $0$. Distances to one target: reverse the edges. $k$-th
shortest walk: let every vertex be popped up to $k$ times.]

#t[Negative weights][SPFA (`spfa.h`) or Bellman–Ford; a negative cycle
exists iff some shortest path needs $n$ edges. Vertices with distance
$-infinity$: those reachable from a vertex that is still relaxed in
round $n$. Johnson: potentials $h$ = distances from a virtual source
joined to all vertices by $0$ edges; then
$w'(u, v) = w + h(u) - h(v) >= 0$, run Dijkstra.]

#t[Difference constraints][$x_v - x_u <= w$ for each constraint
becomes an edge $u -> v$ of weight $w$. Feasible iff there is no
negative cycle; then $x$ = distances from a virtual source (all
start at $0$). $x_v - x_u >= w$ is $x_u - x_v <= -w$.]

#t[MST facts][The lightest edge across any cut is in some MST; the
heaviest edge of a cycle can be dropped. The MST minimises the
largest edge on every path (bottleneck paths are its tree paths).
Second best MST: add one non-tree edge, drop the largest edge on its
tree path (binary lifting max).]

#t[Kruskal tree][During Kruskal, for each merge create a new node of
weight $w$ whose children are the two roots. The vertices reachable
from $v$ using edges of weight $<= x$ are the leaves under the highest
ancestor of $v$ with weight $<= x$ (binary lifting), a contiguous range
in DFS order.]

#t[Structure][Bipartite iff no odd cycle: BFS 2-colouring, or a DSU
with parities online. Functional graphs (one outgoing edge per vertex):
every component is one cycle with trees hanging into it; $k$ steps by
binary lifting. Shortest cycle in an unweighted graph: BFS from every
vertex, $O(n m)$. Bridges and articulation points: `lowlink.h`.]

#t[Modelling with cuts][Choose a set of projects with profits $p_i$
and prerequisites: source to $i$ with capacity $p_i$ if $p_i > 0$, $i$
to sink with $-p_i$ otherwise, $i -> j$ with capacity $infinity$ if $i$
needs $j$. Answer: (sum of positive profits) $-$ min cut. Vertex
capacities: split $v$ into $v_"in" -> v_"out"$.]
