/**
 * Name: Li Chao tree
 * Description: Lines $k x + m$ on the integer domain $[l o, h i)$;
 *   `query(x)` is the maximum at $x$ (`LLONG_MIN / 2` if no line
 *   covers $x$). `add` inserts a line everywhere, `addSeg` only on
 *   $[a, b)$. Minimum: insert `Line{-k, -m}` and negate the answer.
 *   Each node keeps the line that wins at its midpoint; the loser
 *   can still win on one side only, so it moves down that side.
 *   Hence it works unchanged for any functions of which two cross
 *   at most once (edit `Line`), e.g. $a(x - b)^2 + c$ with one $a$.
 *   Memory $O(C)$ for $C = h i - l o$: for a huge domain, compress
 *   the query points or use the line container (`cht.h`).
 * Time: $O(log C)$, `addSeg` $O(log^2 C)$
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
  void addSeg(Line ln, int a, int b) { seg(ln, a, b, 1, lo, hi); }
  void seg(Line ln, int a, int b, int x, int l, int r) {
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) return add(ln, x, l, r);
    int m = l + (r - l) / 2;
    seg(ln, a, b, 2 * x, l, m);
    seg(ln, a, b, 2 * x + 1, m, r);
  }
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
