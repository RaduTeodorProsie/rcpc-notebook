/**
 * Name: 2-SAT
 * Description: Variables $0..n-1$; a literal is `x` or `~x`
 *   (negation; not `-x`, as $-0 = 0$). Constraints: `either(a, b)` ($a or b$),
 *   `implies`, `force(a)` ($a$ true), `same` ($a = b$), `differ`
 *   ($a != b$, xor), `atMostOne(lits)`. Not 2-SAT: "at least one
 *   of 3+ literals". `solve` fills `val` with a satisfying
 *   assignment or returns false; $x$ is true iff its component
 *   comes after $not x$ in topological order. `atMostOne` with
 *   $O(k)$ clauses (pairwise would be $O(k^2)$): a new variable
 *   $p_i$ means "one of $l_0..l_i$ is true", with $l_i => p_i$,
 *   $p_(i-1) => p_i$ and $p_(i-1) => not l_i$ (once one is true,
 *   all later ones are false).
 * Time: $O(n + m)$
 * Usage: TwoSat s(n); s.either(a, ~b); s.solve(val);
 */
#pragma once
#include "scc.h"
struct TwoSat {
  int n;
  vector<vi> g;
  TwoSat(int n) : n(n), g(2 * n) {}
  int addVar() { return g.resize(2 * ++n), n - 1; }
  int id(int x) { return x < 0 ? 2 * ~x + 1 : 2 * x; }
  void either(int a, int b) {
    g[id(a) ^ 1].push_back(id(b));
    g[id(b) ^ 1].push_back(id(a));
  }
  void implies(int a, int b) { either(~a, b); }
  void force(int a) { either(a, a); }
  void same(int a, int b) { implies(a, b), implies(b, a); }
  void differ(int a, int b) { same(a, ~b); }
  void atMostOne(const vi& li) {
    if (sz(li) < 2) return;
    int p = li[0]; // p: some literal before i is true
    rep(i, 1, sz(li)) {
      int q = addVar();
      implies(p, ~li[i]), implies(p, q), implies(li[i], q);
      p = q;
    }
  }
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
