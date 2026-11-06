// Name: Sums
#import "/snippets/sheet.typ": sec
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  sec[Closed forms],
  [Powers], [$sum_(i=1)^n i^2 = n(n+1)(2n+1)\/6$, #h(3pt) $sum_(i=1)^n i^3 = (n(n+1)\/2)^2$],
  [Geometric], [$sum_(i=0)^(n-1) r^i = (r^n - 1)\/(r - 1)$, #h(3pt) $sum_(i>=0) i r^i = r\/(1-r)^2$],
  sec[Sums of powers],
  [Bernoulli], [$B_0, dots, B_8 = 1, -1\/2, 1\/6, 0, -1\/30, 0, 1\/42, 0, -1\/30$, and $B_k = 0$ for odd $k > 1$. More: $sum_(k=0)^m binom(m+1, k) B_k = 0$ for $m >= 1$. EGF: $x\/(e^x - 1)$],
  [Faulhaber], [$sum_(i=0)^(n-1) i^m = 1\/(m+1) dot sum_(k=0)^m binom(m+1, k) B_k n^(m+1-k)$. \
    A polynomial in $n$ of degree $m + 1$: or interpolate it from $m + 2$ values],
  [Euler– \ Maclaurin], [#set par(leading: 1.1em)
    for a smooth $f$: \
    $sum_(i=a)^(b-1) f(i) approx integral_a^b f(x) d x + (f(a) - f(b))\/2$ \
    $+ (f'(b) - f'(a))\/12 - (f'''(b) - f'''(a))\/720$ \
    e.g. $H_n = sum_(i=1)^n 1\/i approx ln n + 0.5772 + 1\/(2n)$],
)
