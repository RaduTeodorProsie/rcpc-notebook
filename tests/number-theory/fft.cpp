#include "number-theory/fft.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {
    int n = rnd(0, 2000), m = rnd(0, 2000);
    auto a = rvec(n, -10000, 10000), b = rvec(m, -10000, 10000);
    auto r = fconv(a, b);
    vector<ll> w(n && m ? n + m - 1 : 0);
    rep(i, 0, n) rep(j, 0, m) w[i + j] += a[i] * b[j];
    CHECK(r == w, "n=%d m=%d", n, m);
  }
  vector<ll> a(1 << 18, 1000), b(1 << 18, 1000);
  auto r = fconv(a, b);
  rep(i, 0, sz(r)) CHECK(r[i] == 1000000ll * min<ll>(i + 1, sz(r) - i));
}
