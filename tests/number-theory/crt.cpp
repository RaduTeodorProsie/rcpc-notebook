#include "number-theory/crt.h"
#include "testlib.h"
int main() {
  rep(it, 0, 3000) {
    ll m = rnd(1, 300), n = rnd(1, 300), a = rnd(0, m - 1), b = rnd(0, n - 1);
    auto [x, l] = crt(a, m, b, n);
    ll L = lcm(m, n), want = -1;
    rep(v, 0, L) if (v % m == a && v % n == b) { want = v; break; }
    CHECK(x == want, "a=%lld m=%lld b=%lld n=%lld got %lld", a, m, b, n, x);
    if (want >= 0) CHECK(l == L);
    ll p = rnd(-1e9, 1e9), q = rnd(-1e9, 1e9), u, v;
    ll g = euclid(p, q, u, v);
    CHECK(abs(g) == gcd(p, q) && (__int128)p * u + (__int128)q * v == g);
  }
  // large moduli
  rep(it, 0, 1000) {
    ll m = rnd(1, 1e12), n = rnd(1, 1e6), x0 = rnd(0, 1e15);
    auto [x, l] = crt(x0 % m, m, x0 % n, n);
    CHECK(x >= 0 && x < l && x % m == x0 % m && x % n == x0 % n);
  }
}
