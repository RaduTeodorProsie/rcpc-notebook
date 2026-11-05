// Name: Greedy and exchange arguments
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Exchange argument][To find the best order, compare two adjacent
items $a, b$: put $a$ first iff that is no worse than $b$ first. If
this comparison is a consistent order (a key, or transitive), sorting
by it is optimal. Minimise $sum w_i C_i$ ($C_i$ = completion time,
$t_i$ = length): $a$ first iff $t_a w_b < t_b w_a$. Smallest
concatenation: $a$ first iff $a + b < b + a$. Stack boxes or soldiers
with (weight, strength): sort by weight $+$ strength.]

#t[Matroids][Greedy by decreasing weight, keeping an element if the
set stays independent, gives a maximum weight basis exactly when
independence forms a matroid: forests (Kruskal), linearly independent
vectors (XOR basis), unit jobs with deadlines (a set is feasible iff
for every $t$ at most $t$ of its jobs have deadline $<= t$).]

#t[Regret][Take greedily and keep a priority queue of choices to
undo. Jobs with deadlines and profits: by deadline, push each
profit to a min-heap; if the heap is larger than the deadline, pop
its minimum. Buy and sell one unit per day: for price $p$, if the
heap's minimum $m < p$, gain $p - m$, pop $m$ and push $p$ twice
(selling at $p$ can later turn into buying at $p$); otherwise push
$p$.]

#t[Intervals][Most disjoint intervals: by right end, take the next
that starts after the last taken one ends. Fewest points stabbing
all intervals: the same order, put a point at each right end. Cover
a segment with fewest intervals: by left end, always extend to the
farthest right end among those starting inside the covered part.]

#t[Merging][Huffman: repeatedly merge the two smallest, the cost
of a merge being the sum. Lexicographically smallest answer: fix
positions left to right, at each try the smallest value for which
the rest can still be completed (needs a fast feasibility check).]

#t[Small answers][Sometimes the answer is at most $2$ or $3$: check
those cases directly. Prefix gcd, OR or AND changes only $O(log V)$
times, so the distinct values over all subarrays ending at $i$ are
few. The LIS of a random permutation is about $2 sqrt(n)$.]

#t[Monotonicity][If moving the left end right never moves the best
right end left, use two pointers, $O(n)$. Always prove the greedy, or
stress test it against a brute force.]
