// Name: Fracturing search
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Problem][The $k$ best of a huge set of candidates (subsets, paths,
spanning trees, choices of one element per list).]

#t[Method][Arrange the candidates as a tree in which every candidate
appears exactly once, every child is no better than its parent, and
each node has at most $D$ children that are easy to list. Then pop
the best from a priority queue $k$ times, starting from the root and
pushing the children of each popped node:
$O(k D log(k D))$.]

#t[Subset sums][The $k$ smallest sums of non-empty subsets of
$a_1 <= dots <= a_n$, all $a_i >= 0$. The root is ${a_1}$. A subset whose
largest index is $i < n$ has two children: add $a_(i+1)$, or replace
$a_i$ by $a_(i+1)$. Each subset arises once and children are never
smaller.]

#t[One per list][The $k$ smallest sums choosing one element from
each of $m$ sorted lists. Subtract the first elements (all-first is
the best choice), drop lists of length $1$, sort the rest by their
second element, and let a state be (list $i$, index $j$ in it),
meaning lists after $i$ are still at index $0$; start from (list
$1$, index $1$). Children: move to index
$j + 1$ in list $i$; move on to list $i + 1$ at index $1$; and if $j = 1$,
also put list $i$ back to $0$ and take list $i + 1$ at index $1$.]

#t[Alternative][Binary search the $k$-th value $v$: count the
candidates $<= v$ with a DFS that stops after $k$ hits. That costs
$O(k D)$ per step, $O(k D log A)$ in total, without a heap.]
