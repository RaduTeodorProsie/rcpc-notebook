/**
 * Name: Segment tree
 * Description: Point set, query of $[l, r)$ for any associative
 *   `op` with identity `id` (the marked lines). `maxRight(l, f)`
 *   is the largest $r$ with `f(op(a[l..r)))` true, for `f`
 *   monotone with `f(id)` true; it can return the padded size.
 * Usage: Seg s(n); s.set(i, v); s.query(l, r);
 *   // first i >= l with a[i] >= x (op = max):
 *   min(n, s.maxRight(l, [&](ll v) { return v < x; }))
 * Time: $O(log n)$
 */
#pragma once
struct Seg {
  using T = ll; //!
  T id = LLONG_MIN / 2; // /2: safe to negate //!
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
