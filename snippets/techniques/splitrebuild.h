/**
 * Name: Split and rebuild
 * Description: Sqrt on queries. The array is a list of pieces of
 *   a flat array `a` (piece = range of `a`, maybe reversed).
 *   `split(i)` cuts so that a piece starts at position $i$ and
 *   returns its index; a query on $[l, r)$ calls `split(l)`,
 *   `split(r)` and works on the whole pieces between: reverse
 *   their order, move them, sum them with prefix sums of `a`.
 *   Each query adds at most two pieces; every $B approx sqrt(n)$
 *   queries `rebuild` writes the list back into a flat array
 *   (forgetting it makes every query $O(q)$). Keep any
 *   per-piece data computable from `a` alone (prefix sums here).
 * Time: $O(B)$ per query, $O(n)$ per rebuild
 */
#pragma once
struct SplitRebuild {
  struct P { int l, r; bool rev; };
  vector<ll> a, pre;
  vector<P> ps;
  SplitRebuild(const vector<ll>& v) : a(v) { rebuild(); }
  void rebuild() {
    vector<ll> b;
    for (auto [l, r, rev] : ps)
      rep(i, l, r) b.push_back(a[rev ? l + r - 1 - i : i]);
    if (sz(ps)) a.swap(b);
    pre.assign(sz(a) + 1, 0);
    rep(i, 0, sz(a)) pre[i + 1] = pre[i] + a[i];
    ps = {{0, sz(a), false}};
  }
  int split(int i) {
    int k = 0;
    for (; k < sz(ps) && i >= ps[k].r - ps[k].l; ++k)
      i -= ps[k].r - ps[k].l;
    if (k == sz(ps) || !i) return k;
    P& x = ps[k];
    P y = x;
    if (x.rev) x.l = y.r = x.r - i;
    else x.r = y.l = x.l + i;
    ps.insert(ps.begin() + k + 1, y);
    return k + 1;
  }
  void reverse(int l, int r) {
    int i = split(l), j = split(r);
    std::reverse(ps.begin() + i, ps.begin() + j);
    rep(k, i, j) ps[k].rev ^= 1;
  }
  ll sum(int l, int r) {
    int i = split(l), j = split(r);
    ll s = 0;
    rep(k, i, j) s += pre[ps[k].r] - pre[ps[k].l];
    return s;
  }
};
