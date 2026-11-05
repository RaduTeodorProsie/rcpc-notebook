// Name: Useful numbers
#table(
  columns: (auto, 1fr), stroke: none, inset: (x: 2pt, y: 1.8pt),
  fill: (_, y) => if calc.odd(y) { luma(238) },
  [Primes], [`1e9+7`, `1e9+9`, `1000003`, $2^61 - 1$],
  [NTT primes], [$998244353 = 119 dot 2^23 + 1$, $167772161 = 5 dot 2^25 + 1$, \ $469762049 = 7 dot 2^26 + 1$],
  [Primitive root], [$g$ is a primitive root mod $p$ if $g^1, dots, g^(p-1)$ hit every nonzero residue. It is $3$ for the three NTT primes (NTT uses it to build roots of unity) and $5$ for `1e9+7`. Test: $g^((p-1)\/q) != 1$ for every prime $q | p - 1$],
  [Prime count], [$pi(10^6) = 78498$, $pi(10^7) = 664579$, $pi(10^9) approx 5.1 dot 10^7$],
  [Max divisors], [$n <= 10^6$: 240, #h(2pt) $10^9$: 1344, #h(2pt) $10^12$: 6720, #h(2pt) $10^18$: 103680],
  [Factorials], [$10! approx 3.6 dot 10^6$, $13! approx 6.2 dot 10^9$, $20! approx 2.4 dot 10^18$ (fits `ll`)],
  [Limits], [`int` $approx 2.1 dot 10^9$, `ll` $approx 9.2 dot 10^18$, `__int128` $approx 1.7 dot 10^38$],
)
