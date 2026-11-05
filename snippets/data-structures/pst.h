/**
 * Name: Persistent segment tree
 * Description: Point assignment and query of $[l, r)$ for any
 *   associative `op` with identity `id` (marked lines), keeping
 *   every version: `set` returns a new root and old roots stay
 *   valid. Root $0$ is the array of $n$ copies of `id`. For the
 *   $k$-th smallest of $a[l..r)$: version $i$ counts the values in
 *   $a[0..i)$; walk down roots $r$ and $l$ together, comparing the
 *   difference of the left children's counts with $k$.
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
