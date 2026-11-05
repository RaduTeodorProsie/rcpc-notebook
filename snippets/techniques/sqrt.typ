// Name: Sqrt and bitset tricks
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Heavy and light][Call an object heavy if its size is above
$B approx sqrt(n)$; there are at most $n\/B$ heavy ones. Precompute
answers for the heavy ones, brute-force the light ones in $O(B)$.
Triangles: direct each edge towards the endpoint of larger degree
(ties by index); every vertex then has $O(sqrt(m))$ out-edges, and
checking all out-out pairs takes $O(m sqrt(m))$.]

#t[Blocks][Split the array into blocks of size $B$, keep a summary
and a lazy tag per block: an update or query touches $O(n\/B)$ whole
blocks and $O(B)$ single elements. Per-block sorted copies answer
"count $< x$" in $O((n\/B) log B)$. Pick $B$ to balance both sides,
e.g. $sqrt(n log n)$ when one side pays a log.]

#t[Sqrt on queries][Keep a static structure and a buffer of recent
updates; a query asks the static part and scans the buffer. Every
$B$ updates, rebuild the static part in $O(n)$; queries cost
$O(B)$ extra, so $B approx sqrt(n)$ balances. For reversals, cut and paste, see split and rebuild.]

#t[Few distinct sizes][If sizes sum to $n$, there are at most
$sqrt(2n)$ distinct sizes. Knapsack over parts that sum to $n$: group
equal sizes and do a bounded knapsack per size (binary splitting or a
per-residue sweep), $O(n sqrt(n))$.]

#t[Meet in the middle][$n <= 40$ subsets: list the $2^(n\/2)$ sums of
each half, sort one, and binary search or sweep two pointers with
the other. Also for paths of length $k$ (meet at step $k\/2$) and for
"reach the target in at most $k$ moves" (BFS from both ends).]

#t[Bitset][$64 times$ faster boolean DP. Subset sum: `b |= b << w`, in
$O(n W\/64)$. Reachability in a DAG: in reverse topological order,
`r[v] |= r[u]` for every edge, $O(n m\/64)$. Triangles or common
neighbours: `(adj[u] & adj[v]).count()`. Search with `_Find_first()`
and `_Find_next(i)`. The size must be a constant: use the maximum, or
a template over sizes $2^k$ chosen at run time.]

#t[Mo's ordering][Offline range queries where the window moves one
element at a time: `mo.frag`. On trees, use the Euler tour (each
vertex twice, count it only when it appears an odd number of times in
the window, handle the LCA separately).]
