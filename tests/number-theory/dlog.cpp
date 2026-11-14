#include "number-theory/dlog.h"
#include "testlib.h"
int main() {
  rep(m, 1, 120) rep(a, 0, m) rep(b, 0, m) {
    ll want = -1, p = 1 % m;
    rep(x, 0, 2 * m + 2) {
      if (p == b) { want = x; break; }
      p = p * a % m;
    }
    CHECK(dlog(a, b, m) == want, "a=%d b=%d m=%d got %lld want %lld", a, b, m, dlog(a, b, m), want);
  }
  rep(it, 0, 200) {
    ll m = rnd(2, 1e9), a = rnd(0, m - 1), x = rnd(0, 1000), b = 1 % m;
    rep(i, 0, x) b = b * a % m;
    ll r = dlog(a, b, m), c = 1 % m;
    CHECK(r >= 0 && r <= x);
    rep(i, 0, r) c = c * a % m;
    CHECK(c == b);
  }
  // large moduli: every product needs more than 64 bits
  rep(it, 0, 8) {
    ll m = rnd(4e9, 2e12), a = rnd(2, m - 1), x = rnd(0, 3e6);
    auto pw = [&](ll e) {
      ll r = 1 % m, c = a;
      for (; e; e >>= 1, c = ll((__int128)c * c % m))
        if (e & 1) r = ll((__int128)r * c % m);
      return r;
    };
    ll b = pw(x), r = dlog(a, b, m);
    CHECK(r >= 0 && r <= x && pw(r) == b, "a=%lld m=%lld x=%lld got %lld", a, m, x, r);
  }
}
