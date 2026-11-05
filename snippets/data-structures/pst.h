/**
 * Name: Persistent segment tree
 * Description: Point update and query of $[l, r)$ for any
 *   associative `op` with identity `id` (marked lines), keeping
 *   every version: `set` copies the $O(log n)$ nodes on the path
 *   to $i$ and returns the new root; old roots stay valid. Root $0$
 *   is the array of $n$ copies of `id`. To change what an update
 *   does, edit the leaf line: `t[y].v = op(t[x].v, v)` is point add.
 *   Node $x$ covers the same range $[l o, h i)$ in every version, so
 *   two versions can be walked down side by side (`kth`).
 * Time: $O(log n)$ time and new nodes per operation
 */
#pragma once
struct PST {
  using T = ll; //!
  T id = 0; //!
  T op(T a, T b) { return a + b; } //!
  struct N { int l, r; T v; };
  int n;
  vector<N> t;
  PST(int n) : n(n), t{{0, 0, id}} {}
  int set(int rt, int i, T v) {
    return upd(rt, 0, n, i, v);
  }
  int upd(int x, int lo, int hi, int i, T v) {
    int y = sz(t);
    t.push_back(t[x]);
    if (hi - lo == 1) return t[y].v = v, y;
    int m = (lo + hi) / 2;
    if (i < m) {
      int c = upd(t[x].l, lo, m, i, v);
      t[y].l = c;
    } else {
      int c = upd(t[x].r, m, hi, i, v);
      t[y].r = c;
    }
    t[y].v = op(t[t[y].l].v, t[t[y].r].v);
    return y;
  }
  T query(int rt, int l, int r) {
    return qry(rt, 0, n, l, r);
  }
  T qry(int x, int lo, int hi, int l, int r) {
    if (!x || r <= lo || hi <= l) return id;
    if (l <= lo && hi <= r) return t[x].v;
    int m = (lo + hi) / 2;
    return op(qry(t[x].l, lo, m, l, r),
              qry(t[x].r, m, hi, l, r));
  }
};
// --- uses ---
// Version i counts the values in a[0..i), values in [0, n):
//   rt[i + 1] = p.set(rt[i], a[i], p.query(rt[i], a[i],
//                                          a[i] + 1) + 1);
// Count of values below x in a[l..r): query(rt[r], 0, x) -
// query(rt[l], 0, x). k-th smallest (0-indexed) of a[l..r):
// at each node, the left child of R minus that of L
// counts the values of a[l..r) in the left half; go left
// if k is below that count.
int kth(PST& p, int L, int R, int k) {
  auto& t = p.t;
  int lo = 0, hi = p.n;
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    ll c = t[t[R].l].v - t[t[L].l].v;
    if (k < c) L = t[L].l, R = t[R].l, hi = m;
    else k -= c, L = t[L].r, R = t[R].r, lo = m;
  }
  return lo;
}
