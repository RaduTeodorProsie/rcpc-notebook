/**
 * Name: Offline 2D Fenwick tree
 * Description: Point add at $(x, y)$, sum over $x' < x$, $y' < y$,
 *   for $0 <= x < n$ (compress $x$) and any `int` $y$. Every
 *   point that will be updated must first go through `fake`;
 *   then `init()`, then use `add` and `sum` freely.
 * Usage: Fenwick2D f(n); f.fake(x, y); ...; f.init();
 * Time: $O(log^2 n)$ per operation, $O(k log k)$ memory for
 *   $k$ fake points
 */
#pragma once
#include "fenwick.h"
struct Fenwick2D {
  vector<vi> ys;
  vector<Fenwick> f;
  Fenwick2D(int n) : ys(n + 1) {}
  void fake(int x, int y) {
    for (++x; x < sz(ys); x += x & -x) ys[x].push_back(y);
  }
  void init() {
    for (vi& v : ys) {
      sort(all(v)), v.erase(unique(all(v)), v.end());
      f.emplace_back(sz(v));
    }
  }
  int ind(int x, int y) {
    return int(lower_bound(all(ys[x]), y) - ys[x].begin());
  }
  void add(int x, int y, ll v) {
    for (++x; x < sz(ys); x += x & -x)
      f[x].add(ind(x, y), v);
  }
  ll sum(int x, int y) {
    ll r = 0;
    for (; x > 0; x -= x & -x) r += f[x].sum(ind(x, y));
    return r;
  }
};
