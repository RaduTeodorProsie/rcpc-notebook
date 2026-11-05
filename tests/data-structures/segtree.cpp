#include "data-structures/segtree.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 70);
    Seg s(n);
    vector<ll> a(n, LLONG_MIN / 2);  // = id
    rep(q, 0, 300) {
      int i = rnd(0, n - 1);
      a[i] = rnd(-100, 100);
      s.set(i, a[i]);
      int l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      ll w = LLONG_MIN / 2;
      rep(j, l, r) w = max(w, a[j]);
      CHECK(s.query(l, r) == w);
      CHECK(-s.query(l, r) == -w);  // min by negation, empty ranges too
      ll x = rnd(-100, 101);
      int want = l;
      while (want < n && a[want] < x) ++want;
      int got = min(n, s.maxRight(l, [&](ll v) { return v < x; }));
      CHECK(got == want, "l=%d x=%lld got %d want %d", l, x, got, want);
    }
  }
}
