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
  ull x = 0, y = 0, prd = 2, c = 1, q;
  auto f = [&](ull v) { // v * v + c mod n, even past 2^64
    ull r = mulm(v, v, n) + c;
    return r < c || r >= n ? r - n : r;
  };
  for (int t = 0; t % 40 || __gcd(prd, n) == 1; ++t) {
    if (x == y) ++c, x = rng() % n, y = f(x); // restart
    if ((q = mulm(prd, x > y ? x - y : y - x, n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
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
