// Name: Theorems: counting, games
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Burnside][The number of objects up to a group $G$ of symmetries is
the _average number of objects left unchanged_ by a symmetry:
$1/(|G|) sum_(g in G) "fix"(g)$, over all of $G$, the identity too.
Colourings of positions with $k$ colours: $g$ permutes the positions
and leaves a colouring unchanged iff it is constant on every cycle of
$g$, so $"fix"(g) = k^("cycles of" g)$; with restrictions on the
colours, count those colourings by a DP over the cycles. \
_Rotations:_ rotating $n$ positions by $i$ has $gcd(i, n)$ cycles, so
necklaces of length $n$ up to rotation:
$1/n sum_(d|n) phi(d) k^(n\/d)$. \
_Rotations and reflections_ ($|G| = 2n$): the reflections add
$n k^((n+1)\/2)$ for odd $n$ and $n/2 (k^(n\/2) + k^(n\/2+1))$ for
even $n$. \
_Faces of a cube_ ($24$ rotations):
$(k^6 + 3k^4 + 12k^3 + 8k^2)\/24$.]

#t[Pick][For a simple polygon with lattice-point vertices:
area $=$ interior points $+$ boundary points$\/2 - 1$. A segment
contains $gcd(|Delta x|, |Delta y|) + 1$ lattice points, so the
boundary has $B = sum gcd$ over the edges. Typical use:
interior points $= A - B\/2 + 1$ with $A$ from the shoelace formula.]

#t[Sprague–Grundy][For games where both players have the same moves,
play always ends, and whoever cannot move loses. A position's Grundy
value is the mex of the values of the positions reachable in one move;
it is lost for the player to move iff the value is $0$. A sum of
independent games (a move is a move in one of them) has the XOR of
their values; so does a position that a move splits into independent
parts. Nim: a pile of size $x$ has value $x$. \
_Misère Nim_ (the last move loses): the same winner as in Nim, unless
every pile is $<= 1$: then the player to move wins iff the number of
piles of size $1$ is even. \
_Staircase Nim_ (a move takes coins from step $i$ down to step
$i - 1$; step $0$ is the floor): XOR of the odd steps.]
