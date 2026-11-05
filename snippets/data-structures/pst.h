/**
 * Name: Persistent segment tree
 * Description: Point add, range sum; every `add` returns a new
 *   root and old roots stay valid. Root $0$ is the empty tree.
 *   Uses: $k$-th smallest in a subarray (values in $[0, n)$).
 * Time: $O(log n)$, $O(log n)$ new nodes per update
 */
#pragma once
struct PST {
  struct N { int l, r; ll s; };
  vector<N> t{{0, 0, 0}};
  int n;
  PST(int n) : n(n) {}
  int add(int rt, int i, ll v) {
    return upd(rt, 0, n, i, v);
  }
  int upd(int x, int lo, int hi, int i, ll v) {
    int y = sz(t);
    t.push_back(t[x]);
    t[y].s += v;
    if (hi - lo > 1) {
      int m = (lo + hi) / 2;
      if (i < m) {
        int c = upd(t[x].l, lo, m, i, v);
        t[y].l = c;
      } else {
        int c = upd(t[x].r, m, hi, i, v);
        t[y].r = c;
      }
    }
    return y;
  }
  ll sum(int rt, int l, int r) {
    return qry(rt, 0, n, l, r);
  }
  ll qry(int x, int lo, int hi, int l, int r) {
    if (!x || r <= lo || hi <= l) return 0;
    if (l <= lo && hi <= r) return t[x].s;
    int m = (lo + hi) / 2;
    return qry(t[x].l, lo, m, l, r) +
           qry(t[x].r, m, hi, l, r);
  }
};
// --- uses ---
// roots[i+1] = add(roots[i], a[i], 1). k-th (0-based)
// smallest of a[l..r) is kth(roots[l], roots[r], k).
int kth(PST& p, int L, int R, ll k) {
  int lo = 0, hi = p.n;
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    ll c = p.t[p.t[R].l].s - p.t[p.t[L].l].s;
    if (k < c) L = p.t[L].l, R = p.t[R].l, hi = m;
    else k -= c, L = p.t[L].r, R = p.t[R].r, lo = m;
  }
  return lo;
}
