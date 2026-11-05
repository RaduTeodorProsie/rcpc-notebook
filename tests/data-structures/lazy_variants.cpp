// variants: data-structures/lazy.h data-structures/lazyvar.frag
#include VARIANT_FILE
#include "testlib.h"
int main() {
  const ll P = 998244353;
  rep(it, 0, 300) {
    int n = rnd(1, 60);
    vector<ll> a = rvec(n, 0, 50);
    vector<Lazy::T> init(n);
#if VARIANT == 0
    rep(i, 0, n) init[i] = {a[i], a[i], 1};
#else
    rep(i, 0, n) init[i] = {a[i], 1};
#endif
    Lazy s(init);
    rep(q, 0, 300) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n);
      if (rnd(0, 1)) {
#if VARIANT == 0
        ll v = rnd(-30, 30);
        s.update(l, r, v);
        rep(j, l, r) a[j] = v;
#elif VARIANT == 1
        ll b = rnd(0, P - 1), c = rnd(0, P - 1);
        s.update(l, r, {b, c});
        rep(j, l, r) a[j] = (b * a[j] + c) % P;
#else
        ll v = rnd(-5, 5);
        s.update(l, r, v);
        rep(j, l, r) a[j] += v;
#endif
      } else {
        auto t = s.query(l, r);
#if VARIANT == 0
        ll sm = 0, mn = LLONG_MAX;
        rep(j, l, r) sm += a[j], mn = min(mn, a[j]);
        CHECK(t.sum == sm && t.mn == mn);
#elif VARIANT == 1
        ll sm = 0;
        rep(j, l, r) sm = (sm + a[j]) % P;
        CHECK(t.sum == sm);
#else
        ll mx = *max_element(a.begin() + l, a.begin() + r);
        CHECK(t.mx == mx && t.cnt == count(a.begin() + l, a.begin() + r, mx));
        auto e = s.query(l, l);  // empty: identity, safe to negate
        CHECK(e.cnt == 0 && -e.mx == -(LLONG_MIN / 2));
#endif
      }
    }
  }
}
