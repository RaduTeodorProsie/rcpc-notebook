// Name: Generating functions
#set par(justify: true, spacing: 4.2pt)
#import "/snippets/sheet.typ": t
#t[Ordinary][$A(x) = sum a_n x^n$, where $a_n$ counts objects of size
$n$ built from unlabelled parts. The product $A B$ counts pairs (an
$A$-object, a $B$-object) whose sizes add up:
$[x^n] A B = sum_k a_k b_(n-k)$. Sequences of $A$-objects (none of
size $0$): $1\/(1 - A)$. Items of sizes $w_i$, each used at most once:
$product (1 + x^(w_i))$; any number of times: $product 1\/(1 - x^(w_i))$
(partitions: $w_i = i$). Prefix sums: multiply by $1\/(1 - x)$. Shift
by $s$: multiply by $x^s$.]

#t[Exponential][$hat(A)(x) = sum a_n x^n \/ n!$ for labelled objects
(labels $1..n$ all distinct). The product splits the labels into two
sets and builds one object on each:
$n! [x^n] hat(A) hat(B) = sum_k binom(n, k) a_k b_(n-k)$. Sets of
$A$-objects: $e^(hat(A))$; so all $= e^("connected")$ and connected
$= ln("all")$. Set partitions: $e^(e^x - 1)$ (Bell). Permutations as
sets of cycles: $e^(-ln(1-x)) = 1\/(1-x)$. Graphs:
$sum 2^(binom(n,2)) x^n\/n!$, its $ln$ counts connected graphs.]

#t[Series][$1\/(1-x)^k = sum_n binom(n+k-1, k-1) x^n$, #h(2pt)
$-ln(1-x) = sum_(n>=1) x^n \/ n$, #h(2pt) $e^x = sum x^n\/n!$. Catalan:
$C = 1 + x C^2$, so $C(x) = (1 - sqrt(1 - 4x)) \/ (2x)$. A linear
recurrence of order $k$ has $A = P(x)\/Q(x)$ with
$Q = 1 - c_1 x - dots - c_k x^k$ and $deg P < k$.]

#t[Computing][Two factors: NTT. Many small factors: multiply them in a
balanced tree, $O(n log^2 n)$. Modulo $x^(n+1)$ in $O(n^2)$, $b$ being
the result, for $m = 1..n$: \
inverse ($a_0 != 0$): $b_0 = 1\/a_0$,
$b_m = -(1\/a_0) sum_(i=1)^m a_i b_(m-i)$; \
$e^A$ ($a_0 = 0$): $b_0 = 1$, $m b_m = sum_(k=1)^m k a_k b_(m-k)$; \
$ln A$ ($a_0 = 1$): $m b_m = m a_m - sum_(k=1)^(m-1) k b_k a_(m-k)$; \
$A^k$ ($a_0 = 1$, any $k$, even a fraction): $b_0 = 1$,
$m b_m = sum_(i=1)^m (k i - m + i) a_i b_(m-i)$. \
All come from a derivative: $B = A^k$ gives $A B' = k A' B$; compare
the coefficients of $x^(m-1)$.]

#t[Spotting one]["Ways to pick things with total $n$" is a coefficient
of a product. "Arrange labelled things into groups" is an EGF of sets
or sequences. A DP that applies the same convolution at every step is
a power $A^k$: square and multiply, or the $A^k$ recurrence above.]
