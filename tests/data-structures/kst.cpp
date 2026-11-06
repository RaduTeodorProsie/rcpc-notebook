#include "data-structures/kst.h"
#include "testlib.h"
int main() {
  rep(it, 0, 400) {
    int n = rnd(1, 40);
    ll A = rnd(0, 1) ? 3 : 1000, B = rnd(0, 1) ? 20 : 1000000;
    vector<KST::Ln> v(n);
    for (auto& [a, b] : v) a = rnd(-A, A), b = rnd(-B, B);
    if (rnd(0, 3) == 0) v[rnd(0, n - 1)] = {0, -(ll)1e18};  // an empty slot
    KST t(v);
    rep(op, 0, 1500) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n), ty = rnd(0, 3);
      if (ty == 0) {
        ll d = rnd(0, 1) ? rnd(0, 3) : rnd(0, 1000);
        rep(i, l, r) v[i].b += v[i].a * d;
        t.heat(l, r, d);
      } else if (ty == 1) {
        int i = rnd(0, n - 1);
        v[i] = {rnd(-A, A), rnd(-B, B)};
        t.set(i, v[i]);
      } else {
        ll want = LLONG_MIN;
        rep(i, l, r) want = max(want, v[i].b);
        CHECK(t.query(l, r) == want, "it=%d op=%d", it, op);
      }
      // values must stay in range for the snippet's contract; re-seed if they drift far
      if (op % 200 == 199)
        rep(i, 0, n) if (llabs(v[i].b) > (ll)1e15) v[i] = {rnd(-A, A), rnd(-B, B)}, t.set(i, v[i]);
    }
    CHECK(t.query(0, 0) < -(ll)1e18 && -t.query(0, 0) > 0);  // empty range: safe to negate
  }
  {  // empty
    KST t(vector<KST::Ln>{});
    CHECK(t.query(0, 0) < -(ll)1e18);
  }
  {  // zero speeds and huge total heat: nothing may break
    KST t(vector<KST::Ln>(8, {0, 5}));
    rep(i, 0, 8) t.heat(0, 8, (ll)1e18);  // melt would pass INF = 4.6e18
    CHECK(t.query(0, 8) == 5);
  }
  {  // amortized cost: many heats on a big tree finish quickly
    int n = 1 << 17;
    vector<KST::Ln> v(n);
    for (auto& [a, b] : v) a = rnd(0, 1000), b = rnd(-1e9, 1e9);
    KST t(v);
    ll mx = 0;
    rep(op, 0, 200000) {
      int l = rnd(0, n - 1), r = rnd(l + 1, min(n, l + 1000));
      t.heat(l, r, rnd(0, 100));
      mx = max(mx, t.query(0, n));
    }
    CHECK(mx > 0);
  }
}
