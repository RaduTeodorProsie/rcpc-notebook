// Name: Game theory
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Win and lose][Normal play (the player who cannot move loses): a
position is losing iff every move leads to a winning position; in
particular one with no moves is losing. On a DAG, decide states in
reverse topological order.]

#t[Cycles and draws][Retrograde BFS from the terminal positions. When
a position becomes losing, all its predecessors become winning. When
a position becomes winning, decrease a counter of undecided moves in
each predecessor; at $0$ that predecessor is losing. Positions still
undecided at the end are draws. $O(V + E)$.]

#t[Sums of games][Independent games played side by side, one move in
one of them per turn: XOR the Grundy values (Sprague–Grundy). A move
that splits a game into independent parts: the Grundy value is the mex
over all moves of the XOR of the parts (Kayles, splitting piles).
Unknown Grundy function: brute force it for small sizes and look for a
period or pattern; print the table.]

#t[Nim variants][Misère Nim (the last mover loses): play as in normal
Nim, unless every pile is at most $1$; then the player to move wins
iff the number of piles of size $1$ is even. Staircase Nim (move coins
from step $i$ to step $i - 1$, step $0$ is out of play): Nim on the
odd steps. Taking up to $m$ from one pile: Grundy value $x mod (m+1)$.
Taking from up to $k$ piles at once (Moore): lost iff for every bit,
the number of piles with that bit set is divisible by $k + 1$.
Wythoff (take any amount from one pile, or the same amount from both):
lost iff the piles are $(floor(i phi), floor(i phi^2))$, $phi$ the golden
ratio.]

#t[Trees][Green Hackenbush on a rooted tree (cutting an edge removes
everything no longer attached to the root): the Grundy value is the
XOR over the children $c$ of $g(c) + 1$.]

#t[Strategies][Symmetry: the second player copies the first player's
move in the mirrored position, which needs a symmetric start and the
mirror move always being legal. Strategy stealing: if an extra move
never hurts, the first player wins (without a constructive strategy).]

#t[Scores][Both players maximise their own total: let $d(s)$ = score
of the player to move minus the opponent's, from state $s$; then
$d(s) = max_("moves") ("gain" - d(s'))$. E.g. taking from either end
of an array: $d(l, r) = max(a_l - d(l+1, r), a_r - d(l, r-1))$.]
