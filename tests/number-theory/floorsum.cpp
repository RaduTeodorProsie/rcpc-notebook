#include "number-theory/floorsum.h"
#include "testlib.h"
ll fdiv(ll a, ll b) { return a / b - ((a % b != 0) && ((a < 0) != (b < 0))); }
int main() {
  rep(it, 0, 20000) {
    ll n = rnd(0, 200), m = rnd(1, 300), a = rnd(-1000, 1000), b = rnd(-1000, 1000);
    ll w = 0;
    rep(i, 0, n) w += fdiv(a * i + b, m);
    CHECK(floorSum(n, m, a, b) == w, "n=%lld m=%lld a=%lld b=%lld", n, m, a, b);
  }
  rep(it, 0, 200) {
    ll n = rnd(0, 100000), m = rnd(1, 1e9), a = rnd(0, 1e9), b = rnd(0, 1e9);
    __int128 w = 0;
    rep(i, 0, n) w += ((__int128)a * i + b) / m;
    CHECK(floorSum(n, m, a, b) == (ll)w);
  }
  // huge n and negative a/b: intermediate sums overflow ll, the answer does not
  auto ref = [](auto& self, __int128 n, __int128 m, __int128 a, __int128 b) -> __int128 {
    if (n == 0) return 0;
    __int128 r = 0;
    if (a < 0 || a >= m) {
      __int128 q = a / m - (a % m < 0);
      r += n * (n - 1) / 2 * q, a -= q * m;
    }
    if (b < 0 || b >= m) {
      __int128 q = b / m - (b % m < 0);
      r += n * q, b -= q * m;
    }
    __int128 y = a * n + b;
    if (y < m) return r;
    return r + self(self, y / m, a, m, y % m);
  };
  int checked = 0;
  rep(it, 0, 20000) {
    ll n = rnd(0, 4000000000LL), m = rnd(1, rnd(0, 1) ? 100 : 4000000000LL);
    ll a = rnd(-3 * m, 3 * m), b = rnd(-(ll)4e18, (ll)4e18);
    __int128 w = ref(ref, n, m, a, b);
    if (w > (__int128)LLONG_MAX || w < (__int128)LLONG_MIN) continue;
    ++checked;
    CHECK(floorSum(n, m, a, b) == (ll)w, "n=%lld m=%lld a=%lld b=%lld", n, m, a, b);
  }
  CHECK(checked > 2000, "%d", checked);
}
