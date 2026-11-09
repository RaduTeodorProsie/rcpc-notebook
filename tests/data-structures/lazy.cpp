#include "data-structures/lazy.h"
#include "testlib.h"
int main() {
  {
    Lazy e(vector<Lazy::T>{});  // n = 0
    e.update(0, 0, 1);
    e.query(0, 0);
  }
  rep(it, 0, 300) {
    int n = rnd(1, 70);
    vector<ll> a = rvec(n, -50, 50);
    vector<Lazy::T> init(n);
    rep(i, 0, n) init[i] = {a[i], a[i], 1};
    Lazy s(init);
    rep(q, 0, 300) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n);
      if (rnd(0, 1)) {
        ll v = rnd(-30, 30);
        s.update(l, r, v);
        rep(j, l, r) a[j] += v;
      } else {
        auto t = s.query(l, r);
        ll sm = 0, mn = LLONG_MAX;
        rep(j, l, r) sm += a[j], mn = min(mn, a[j]);
        CHECK(t.sum == sm && t.mn == mn && t.len == r - l);
      }
    }
  }
}
