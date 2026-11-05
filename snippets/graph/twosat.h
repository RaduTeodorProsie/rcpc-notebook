/**
 * Name: 2-SAT
 * Description: Variables $0..n-1$; pass `x` or `~x` as a
 *   literal. `solve` fills `val` or returns false.
 * Time: $O(n + m)$
 * Usage: TwoSat s(n); s.either(a, ~b); s.solve(val);
 */
#pragma once
#include "scc.h"
struct TwoSat {
  int n;
  vector<vi> g;
  TwoSat(int n) : n(n), g(2 * n) {}
  int id(int x) { return x < 0 ? 2 * ~x + 1 : 2 * x; }
  void either(int a, int b) {
    g[id(a) ^ 1].push_back(id(b));
    g[id(b) ^ 1].push_back(id(a));
  }
  void implies(int a, int b) { either(~a, b); }
  bool solve(vi& val) {
    SCC s(g);
    val.assign(n, 0);
    rep(i, 0, n) {
      if (s.comp[2 * i] == s.comp[2 * i + 1]) return false;
      val[i] = s.comp[2 * i] < s.comp[2 * i + 1];
    }
    return true;
  }
};
