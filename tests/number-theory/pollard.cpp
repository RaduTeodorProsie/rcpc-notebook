#include "number-theory/pollard.h"
#include "testlib.h"
int main() {
  auto test = [](ull n) {
    auto f = factor(n);
    ull prod = 1;
    for (ull p : f) {
      CHECK(isPrime(p), "%llu in %llu", p, n);
      prod *= p;
    }
    CHECK(prod == n && is_sorted(all(f)), "n=%llu", n);
  };
  rep(n, 1, 20000) test(n);
  rep(it, 0, 2000) test(rnd(1, 4e18));
  rep(it, 0, 100) {
    ull a = rnd(1, 1ll << 31) | 1, b = rnd(1, 1ll << 31) | 1;
    while (!isPrime(a)) a += 2;
    while (!isPrime(b)) b += 2;
    auto f = factor(a * b);
    CHECK(sz(f) == 2 && f[0] * f[1] == a * b);
  }
  test(1ull << 63), test(999999999999999989ull), test(4611686014132420609ull);
}
