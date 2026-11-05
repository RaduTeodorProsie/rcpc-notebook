/**
 * Name: Segment tree
 * Description: Point set, query of $[l, r)$ for any associative
 *   `op` with identity `id` (edit the marked lines). `maxRight`
 *   returns the largest $r$ with `f(op(a[l..r)))` true, for a
 *   monotone `f` with `f(id)` true. Uses: walks.
 * Time: $O(log n)$
 */
#pragma once
struct Seg {
  using T = ll; //!
  T id = LLONG_MIN; //!
  T op(T a, T b) { return max(a, b); } //!
  int n;
  vector<T> t;
  Seg(int m) : n(1) {
    while (n < m) n *= 2;
    t.assign(2 * n, id);
  }
  void set(int i, T v) {
    for (t[i += n] = v; i >>= 1;)
      t[i] = op(t[2 * i], t[2 * i + 1]);
  }
  T query(int l, int r) {
    T a = id, b = id;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) a = op(a, t[l++]);
      if (r & 1) b = op(t[--r], b);
    }
    return op(a, b);
  }
  template <class F> int maxRight(int l, F f) {
    if (l == n) return n;
    T acc = id;
    l += n;
    do {
      while (l % 2 == 0) l >>= 1;
      if (!f(op(acc, t[l]))) {
        while (l < n) {
          l *= 2;
          if (f(op(acc, t[l]))) acc = op(acc, t[l++]);
        }
        return l - n;
      }
      acc = op(acc, t[l++]);
    } while ((l & -l) != l);
    return n;
  }
};
// --- uses ---
// First index i >= l with a[i] >= x (n if none); op = max.
int firstAtLeast(Seg& s, int l, ll x) {
  return s.maxRight(l, [&](ll v) { return v < x; });
}
