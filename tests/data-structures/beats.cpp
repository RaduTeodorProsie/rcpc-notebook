#include "data-structures/beats.h"
#include "testlib.h"
int main() {
  rep(it, 0, 400) {
    int n = rnd(1, 40);
    vector<ll> a = rvec(n, -20, 20);
    Beats b(a);
    rep(q, 0, 200) {
      int l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      ll v = rnd(-25, 25);
      int k = rnd(0, 3);
      if (k == 0) { b.chmin(l, r, v); rep(i, l, r) a[i] = min(a[i], v); }
      if (k == 1) { b.chmax(l, r, v); rep(i, l, r) a[i] = max(a[i], v); }
      if (k == 2) { v /= 5; b.add(l, r, v); rep(i, l, r) a[i] += v; }
      if (k == 3) {
        ll s = 0, mx = -Beats::INF, mn = Beats::INF;
        rep(i, l, r) s += a[i], mx = max(mx, a[i]), mn = min(mn, a[i]);
        auto got = b.query(l, r);
        CHECK(got[0] == s && got[1] == mx && got[2] == mn);
      }
    }
  }
}
