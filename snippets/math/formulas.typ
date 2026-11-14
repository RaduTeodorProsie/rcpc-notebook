// Name: Formulas
#import "/snippets/sheet.typ": sec
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  sec[Number theory],
  [Möbius], [$mu(n) = (-1)^k$ if $n$ is a product of $k$ distinct primes, else $0$. \ $g(n) = sum_(d|n) f(d) <==> f(n) = sum_(d|n) mu(d) g(n\/d)$, #h(3pt) $sum_(d|n) mu(d) = [n = 1]$],
  [Totient], [$phi(n) = \#{1 <= i <= n : gcd(i, n) = 1} = n product_(p|n) (1 - 1\/p)$, #h(3pt) $sum_(d|n) phi(d) = n$],
  [Euler], [$a^e equiv a^(e mod phi(m) + phi(m)) space (mod m)$ for $e >= log_2 m$, any $a$],
  [gcd sums], [$sum_(i=1)^n gcd(i, n) = sum_(d|n) d phi(n\/d)$, #h(3pt) $sum_(i<=n, gcd(i,n)=1) i = n phi(n)\/2$ ($n > 1$)],
  [Lucas], [$binom(n, k) equiv product_i binom(n_i, k_i) space (mod p)$, digits in base $p$],
  [Legendre], [exponent of $p$ in $n!$: $sum_(i>=1) floor(n\/p^i)$. Kummer: exponent of $p$ in $binom(n, k)$ = number of carries when adding $k$ and $n - k$ in base $p$],
  [Wilson], [$(p-1)! equiv -1 space (mod p)$],
  [Inverses], [of $1..n$ modulo a prime $p$ in $O(n)$: $"inv"(1) = 1$, $"inv"(i) = -floor(p\/i) dot "inv"(p mod i)$],
  [Floor blocks], [$floor(n\/i)$ takes at most $2 sqrt(n)$ values; it is constant for $i$ in $[l, r]$ with $r = floor(n \/ floor(n\/l))$: `for (l = 1; l <= n; l = r + 1)`],
  [Frobenius], [$gcd(a, b) = 1$: largest number not of the form $a x + b y$ ($x, y >= 0$) is $a b - a - b$],
  [Fibonacci], [$F_(m+n) = F_m F_(n+1) + F_(m-1) F_n$, #h(3pt) $gcd(F_m, F_n) = F_(gcd(m,n))$],
  sec[Geometry],
  [Triangle], [sides $a, b, c$ opposite the angles $A, B, C$; $s = (a+b+c)\/2$; $R$ = circumradius (circle through the vertices), $r$ = inradius (circle tangent to the sides). Area $S = a b sin C\/2 = sqrt(s(s-a)(s-b)(s-c)) = a b c\/(4R) = r s$],
  [Laws], [$c^2 = a^2 + b^2 - 2 a b cos C$, #h(3pt) $a\/sin A = b\/sin B = c\/sin C = 2R$],
  [Solids], [sphere $4/3 pi r^3$, area $4 pi r^2$; cone $pi r^2 h\/3$; cap of height $h$: $pi h^2 (3r - h)\/3$],
  [Sphere dist.], [$r arccos(sin phi_1 sin phi_2 + cos phi_1 cos phi_2 cos(lambda_1 - lambda_2))$, $phi$ latitude, $lambda$ longitude],
  [Planar graph], [$V - E + F = 1 + C$ ($C$ components, $F$ counts the outer face), #h(3pt) $E <= 3V - 6$],
)
