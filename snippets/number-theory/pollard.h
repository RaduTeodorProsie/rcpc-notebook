/**
 * Name: Pollard rho
 * Description: Prime factors of $n$, sorted, with repeats.
 * Time: $O(n^(1\/4))$ expected
 */
#pragma once
#include "millerrabin.h"
mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count());
ull rho(ull n) {
  if (n % 2 == 0) return 2;
  for (;;) {
    ull c = rng() % (n - 1) + 1, x = rng() % n;
    ull y = x, g = 1;
    auto f = [&](ull v) { return (mulm(v, v, n) + c) % n; };
    while (g == 1) {
      x = f(x), y = f(f(y));
      g = __gcd(x > y ? x - y : y - x, n);
    }
    if (g != n) return g;
  }
}
void factorRec(ull n, vector<ull>& out) {
  if (n == 1) return;
  if (isPrime(n)) return out.push_back(n);
  ull d = rho(n);
  factorRec(d, out), factorRec(n / d, out);
}
vector<ull> factor(ull n) {
  vector<ull> f;
  factorRec(n, f);
  sort(all(f));
  return f;
}
