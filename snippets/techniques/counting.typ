// Name: Counting tricks
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Complement][Count the bad objects and subtract them from the
total when "at least one" or "some pair" is easier to state the other
way round.]

#t[Fix one thing][Fix the maximum, the minimum, the first element, the
value of a gcd or the position of something special; count each case
and sum. Pairs: fix the larger (or later) element. Unordered pairs
$=$ (ordered pairs $+$ symmetric ones)$\/2$.]

#t[Exactly from at least][Let $g(k) = sum_(|S| = k) N(S)$, where
$N(S)$ counts objects having all bad properties in $S$ (others free).
Then exactly $j$ bad properties:
$f(j) = sum_(k >= j) (-1)^(k-j) binom(k, j) g(k)$, and $j = 0$ is plain
incl.–excl. $sum_k (-1)^k g(k)$. Typical: derangements, onto maps,
"no two adjacent equal", "every row has a 1". When $N(S)$ depends only
on $|S|$: $g(k) = binom(m, k) N_k$.]

#t[Bounded stars and bars][Solutions of $x_1 + dots + x_k = n$ with
$0 <= x_i <= c$: incl.–excl. over the $j$ variables forced above $c$
(take $c + 1$ off each):
$sum_j (-1)^j binom(k, j) binom(n - j(c+1) + k - 1, k - 1)$. A lower
bound $x_i >= l$: substitute $x_i = y_i + l$.]

#t[Reflection][Monotone lattice paths $A -> B$ that touch the line
$y = x + 1$ are in bijection with all paths $A' -> B$, $A'$ being $A$
mirrored in that line (mirror the part before the first touch). So
paths $(0,0) -> (n,n)$ never above the diagonal number
$binom(2n, n) - binom(2n, n+1) = C_n$. Ballot: with $a > b$ votes, the
orders in which $A$ stays strictly ahead number
$(a - b)\/(a + b) dot binom(a + b, a)$.]

#t[Distinct choices][Distinct $x_i$ with $1 <= x_i <= c_i$: sort so
that $c_1 <= c_2 <= dots$; the answer is $product_i (c_i - i + 1)$, since
the $i - 1$ earlier choices all lie in $[1, c_i]$.]

#t[Relative order][In all $n!$ permutations, a given set of $k$
elements appears in each of its $k!$ orders equally often: a fixed
order of those $k$ leaves $n! \/ k!$ permutations, and a given one of
them comes first with probability $1\/k$.]

#t[Trees][Labelled trees on $n$ vertices: $n^(n-2)$. With degrees
$d_i$: $(n-2)! \/ product_i (d_i - 1)!$, since in the Prüfer sequence
(repeatedly delete the smallest leaf and write down its neighbour)
vertex $i$ appears $d_i - 1$ times. Forests on $n$ vertices with $k$
trees, rooted at the given vertices $1..k$: $k n^(n-k-1)$. Proper
colourings with $q$ colours: tree $q (q-1)^(n-1)$, cycle
$(q-1)^n + (-1)^n (q-1)$.]
