/**
 * Name: Li Chao tree
 * Description: Insert lines $k x + m$, query the maximum at an
 *   integer $x in [l o, h i)$. For the minimum: insert
 *   `Line{-k, -m}` instead and negate the answer, since
 *   $min(k x + m) = -max(-k x - m)$.
 *   Memory is $O(C)$ for the domain size $C = h i - l o$; for a
 *   large domain use the line container (`cht.h`) instead, or
 *   compress the query points.
 * Time: $O(log C)$ per operation
 */
#pragma once
struct Line {
  ll k, m;
  ll operator()(ll x) const { return k * x + m; }
};
struct LiChao {
  int lo, hi; vector<Line> t;
  LiChao(int lo, int hi) : lo(lo), hi(hi),
      t(4 * (hi - lo), Line{0, LLONG_MIN / 2}) {}
  void add(Line ln) { add(ln, 1, lo, hi); }
  void add(Line ln, int x, int l, int r) {
    int m = l + (r - l) / 2;
    bool lef = ln(l) > t[x](l), mid = ln(m) > t[x](m);
    if (mid) swap(t[x], ln);
    if (r - l == 1) return;
    if (lef != mid) add(ln, 2 * x, l, m);
    else add(ln, 2 * x + 1, m, r);
  }
  ll query(ll q) {
    ll res = LLONG_MIN / 2;
    for (int x = 1, l = lo, r = hi;;) {
      res = max(res, t[x](q));
      if (r - l == 1) return res;
      int m = l + (r - l) / 2;
      if (q < m) x = 2 * x, r = m;
      else x = 2 * x + 1, l = m;
    }
  }
};
