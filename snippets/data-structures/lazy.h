/**
 * Name: Lazy segment tree
 * Description: Range update, range query on $[l, r)$. Edit the
 *   marked lines: node `T`, tag `U`, `op`, `apply` (tag on node)
 *   and `comp` (`f` after `g`). Example: range add, sum and min.
 *   Uses: other tag types.
 * Time: $O(log n)$
 */
#pragma once
struct Lazy {
  struct T { ll sum = 0, mn = LLONG_MAX; int len = 0; }; //!
  using U = ll; //!
  U none = 0; //!
  T op(T a, T b) { //!
    return {a.sum + b.sum, min(a.mn, b.mn), a.len + b.len}; //!
  } //!
  void apply(T& a, U f) { a.sum += f * a.len, a.mn += f; } //!
  U comp(U f, U g) { return f + g; } //!
  int n;
  vector<T> t;
  vector<U> lz;
  Lazy(const vector<T>& v)
      : n(sz(v)), t(4 * n), lz(4 * n, none) {
    build(1, 0, n, v);
  }
  void build(int x, int l, int r, const vector<T>& v) {
    if (r - l == 1) return void(t[x] = v[l]);
    int m = (l + r) / 2;
    build(2 * x, l, m, v), build(2 * x + 1, m, r, v);
    t[x] = op(t[2 * x], t[2 * x + 1]);
  }
  void push(int x) {
    for (int c : {2 * x, 2 * x + 1})
      apply(t[c], lz[x]), lz[c] = comp(lz[x], lz[c]);
    lz[x] = none;
  }
  void update(int l, int r, U f) { upd(l, r, f, 1, 0, n); }
  void upd(int l, int r, U f, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) {
      apply(t[x], f), lz[x] = comp(f, lz[x]);
      return;
    }
    push(x);
    int m = (lo + hi) / 2;
    upd(l, r, f, 2 * x, lo, m);
    upd(l, r, f, 2 * x + 1, m, hi);
    t[x] = op(t[2 * x], t[2 * x + 1]);
  }
  T query(int l, int r) { return qry(l, r, 1, 0, n); }
  T qry(int l, int r, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return T{};
    if (l <= lo && hi <= r) return t[x];
    push(x);
    int m = (lo + hi) / 2;
    return op(qry(l, r, 2 * x, lo, m),
              qry(l, r, 2 * x + 1, m, hi));
  }
};
// --- uses ---
// Range assign: U = ll, none = LLONG_MIN,
//   apply: if (f != none) a.sum = f * a.len, a.mn = f;
//   comp: return f != none ? f : g;
// Affine x -> b x + c: U = pair (b, c), none = (1, 0),
//   apply: sum = b * sum + c * len;
//   comp: (f.b * g.b, f.b * g.c + f.c)
// Leaves: T{v, v, 1}. Empty nodes must stay identities.
