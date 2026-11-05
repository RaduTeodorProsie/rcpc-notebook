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
}
