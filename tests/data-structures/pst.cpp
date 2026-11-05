#include "data-structures/pst.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {
    int n = rnd(1, 50);
    PST p(n);
    vi roots{0};
    vector<vector<ll>> ver{vector<ll>(n)};
    rep(q, 0, 150) {
      int base = rnd(0, sz(roots) - 1), i = rnd(0, n - 1);
      ll v = rnd(-10, 10);
      roots.push_back(p.set(roots[base], i, v));
      ver.push_back(ver[base]);
      ver.back()[i] = v;
      int k = rnd(0, sz(roots) - 1), l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      ll w = 0;
      rep(j, l, r) w += ver[k][j];
      CHECK(p.query(roots[k], l, r) == w);
    }
  }
  rep(it, 0, 100) {  // k-th smallest, as described
    int n = rnd(1, 40);
    vi a(n);
    for (int& x : a) x = rnd(0, n - 1);
    PST p(n);
    vi rt{0};
    rep(i, 0, n) rt.push_back(p.set(rt[i], a[i], p.query(rt[i], a[i], a[i] + 1) + 1));
    rep(q, 0, 50) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n), k = rnd(0, r - l - 1);
      int L = rt[l], R = rt[r], lo = 0, hi = n, kk = k;
      while (hi - lo > 1) {
        int m = (lo + hi) / 2;
        ll c = p.t[p.t[R].l].v - p.t[p.t[L].l].v;
        if (kk < c) L = p.t[L].l, R = p.t[R].l, hi = m;
        else kk -= c, L = p.t[L].r, R = p.t[R].r, lo = m;
      }
      vi b(a.begin() + l, a.begin() + r);
      sort(all(b));
      CHECK(lo == b[k]);
    }
  }
}
