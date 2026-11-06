/**
 * Name: Segment tree beats
 * Description: On $[l, r)$: `chmin` ($a_i = min(a_i, v)$),
 *   `chmax`, `add`; `query` gives sum, max and min. A node keeps
 *   its max, how often it occurs and the strict second max, and
 *   the same for the min. In `upd`, the break condition stops when
 *   the update cannot change the node (`mx <= v` for chmin). The
 *   tag condition (`mx2 < v`) holds when it changes only the
 *   copies of the max: then the sum drops by `(mx - v) * cmx` and
 *   the node is fixed in $O(1)$; otherwise recurse. Other beats
 *   problems keep this split, e.g. range `%= m`: break if
 *   `mx < m`, tag only if `mx == mn` (a constant node: add the
 *   difference).
 * Time: amortized $O(log^2 n)$, $O(log n)$ without `add`
 */
#pragma once
struct Beats {
  static constexpr ll INF = LLONG_MAX / 4;
  struct N {
    ll sum = 0, mx = -INF, mx2 = -INF, mn = INF, mn2 = INF;
    ll add = 0;
    int cmx = 0, cmn = 0, len = 0;
  };
  int n;
  vector<N> t;
  Beats(const vector<ll>& a) : n(sz(a)), t(4 * n) {
    if (n) build(1, 0, n, a);
  }
  void build(int x, int lo, int hi, const vector<ll>& a) {
    if (hi - lo == 1) {
      ll v = a[lo];
      t[x] = {v, v, -INF, v, INF, 0, 1, 1, 1};
      return;
    }
    int m = (lo + hi) / 2;
    build(2 * x, lo, m, a), build(2 * x + 1, m, hi, a);
    pull(x);
  }
  void pull(int x) {
    N &a = t[2 * x], &b = t[2 * x + 1], &c = t[x];
    c.sum = a.sum + b.sum, c.len = a.len + b.len;
    c.mx = max(a.mx, b.mx), c.mn = min(a.mn, b.mn);
    c.cmx = (a.mx == c.mx) * a.cmx + (b.mx == c.mx) * b.cmx;
    c.cmn = (a.mn == c.mn) * a.cmn + (b.mn == c.mn) * b.cmn;
    c.mx2 = max(a.mx == c.mx ? a.mx2 : a.mx,
                b.mx == c.mx ? b.mx2 : b.mx);
    c.mn2 = min(a.mn == c.mn ? a.mn2 : a.mn,
                b.mn == c.mn ? b.mn2 : b.mn);
  }

  // k = 0: chmin, 1: chmax, 2: add; tag condition must hold
  void tag(int x, int k, ll v) {
    N& a = t[x];
    if (k == 2) {
      a.sum += v * a.len, a.mx += v, a.mn += v, a.add += v;
      if (a.mx2 != -INF) a.mx2 += v;
      if (a.mn2 != INF) a.mn2 += v;
    } else if (k == 0) {
      a.sum -= (a.mx - v) * a.cmx;
      if (a.mn == a.mx) a.mn = v;
      else if (a.mn2 == a.mx) a.mn2 = v;
      a.mx = v;
    } else {
      a.sum += (v - a.mn) * a.cmn;
      if (a.mx == a.mn) a.mx = v;
      else if (a.mx2 == a.mn) a.mx2 = v;
      a.mn = v;
    }
  }
  void push(int x) {
    for (int c : {2 * x, 2 * x + 1}) {
      if (t[x].add) tag(c, 2, t[x].add);
      if (t[c].mx > t[x].mx) tag(c, 0, t[x].mx);
      if (t[c].mn < t[x].mn) tag(c, 1, t[x].mn);
    }
    t[x].add = 0;
  }
  void upd(int k, int l, int r, ll v, int x, int lo,
           int hi) {
    N& a = t[x];
    if (r <= lo || hi <= l || (k == 0 && a.mx <= v) ||
        (k == 1 && a.mn >= v))
      return; // break
    if (l <= lo && hi <= r && (k == 2 ||
        (k == 0 && a.mx2 < v) || (k == 1 && a.mn2 > v)))
      return tag(x, k, v); // tag
    push(x);
    int m = (lo + hi) / 2;
    upd(k, l, r, v, 2 * x, lo, m);
    upd(k, l, r, v, 2 * x + 1, m, hi);
    pull(x);
  }
  void chmin(int l, int r, ll v) {
    upd(0, l, r, v, 1, 0, n);
  }
  void chmax(int l, int r, ll v) {
    upd(1, l, r, v, 1, 0, n);
  }
  void add(int l, int r, ll v) {
    upd(2, l, r, v, 1, 0, n);
  }
  array<ll, 3> query(int l, int r) { // sum, max, min
    return qry(l, r, 1, 0, n);
  }
  array<ll, 3> qry(int l, int r, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return {0, -INF, INF};
    if (l <= lo && hi <= r)
      return {t[x].sum, t[x].mx, t[x].mn};
    push(x);
    int m = (lo + hi) / 2;
    auto a = qry(l, r, 2 * x, lo, m);
    auto b = qry(l, r, 2 * x + 1, m, hi);
    return {a[0] + b[0], max(a[1], b[1]), min(a[2], b[2])};
  }
};
