#include "data-structures/fenwick.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 80);
    Fenwick f(n);
    RangeFenwick rf(n);
    vector<ll> a(n), b(n);
    rep(q, 0, 300) {
      int i = rnd(0, n - 1);
      ll v = rnd(0, 20);
      f.add(i, v), a[i] += v;
      int l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      ll w = rnd(-50, 50);
      rf.add(l, r, w);
      rep(j, l, r) b[j] += w;
      int k = rnd(0, n);
      ll s = 0, s2 = 0;
      rep(j, 0, k) s += a[j], s2 += b[j];
      CHECK(f.sum(k) == s && rf.sum(k) == s2);
      ll x = rnd(0, 20 * n);
      int want = 0;
      ll acc = 0;
      while (want < n && acc + a[want] <= x) acc += a[want++];
      CHECK(f.lower(x) == want, "x=%lld", x);
    }
  }
}
