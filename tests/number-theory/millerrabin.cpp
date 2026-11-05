#include "number-theory/millerrabin.h"
#include "testlib.h"
bool slow(ull n) {
  if (n < 2) return false;
  for (ull d = 2; d * d <= n; ++d)
    if (n % d == 0) return false;
  return true;
}
int main() {
  rep(n, 0, 200000) CHECK(isPrime(n) == slow(n), "n=%d", n);
  rep(it, 0, 3000) {
    ull n = rnd(1, 1e12);
    CHECK(isPrime(n) == slow(n), "n=%llu", n);
  }
  for (ull p : {1000000007ull, 998244353ull, 2305843009213693951ull,
                18446744073709551557ull, 4611686018427387847ull})
    CHECK(isPrime(p), "%llu", p);
  for (ull c : {3215031751ull, 2152302898747ull, 3474749660383ull,
                341550071728321ull, 3825123056546413051ull,
                4611686014132420609ull,
                1000000007ull * 998244353ull, 18446744073709551615ull})
    CHECK(!isPrime(c), "%llu", c);
  rep(it, 0, 300) {  // products of two primes near 2^31
    ull a = rnd(1, 1ll << 31) | 1, b = rnd(1, 1ll << 31) | 1;
    while (!slow(a)) a += 2;
    while (!slow(b)) b += 2;
    CHECK(!isPrime(a * b) && isPrime(a) && isPrime(b));
  }
  CHECK(powm(5, 0, 1) == 0 && powm(3, 4, 1000) == 81);
}
