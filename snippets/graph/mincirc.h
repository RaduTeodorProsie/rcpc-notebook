/**
 * Name: Min-cost circulation
 * Description: Each edge has flow in $[l o, h i]$ and a cost per
 *   unit (any sign: negative cycles are fine); `sup[v] += s`
 *   makes $v$ produce $s$ units ($s < 0$: consume). `solve`
 *   returns the cheapest feasible flow's cost, or `LLONG_MAX`;
 *   then `flow(i)` is the flow on edge $i$. Negative edges start
 *   saturated, so the rest is plain min-cost flow from a super
 *   source. Min-cost max $s$–$t$ flow with negative cycles: find
 *   the max flow $F$ first, then add edge $t -> s$ with
 *   $l o = h i = F$.
 * Usage: MinCirc g(n); int i = g.addEdge(a, b, lo, hi, cost);
 * Time: one `MCMF` run with flow $<= sum$ of all bounds
 */
#pragma once
#include "mcmf.h"
struct MinCirc {
  int n;
  MCMF f;
  vector<ll> sup;
  ll base = 0;
  vector<array<ll, 5>> es; // from, index in g, lo, hi, neg
  MinCirc(int n) : n(n), f(n + 2), sup(n) {}
  int addEdge(int a, int b, ll lo, ll hi, ll cost) {
    bool neg = cost < 0;
    ll x = neg ? hi : lo; // flow sent now
    base += x * cost, sup[a] -= x, sup[b] += x;
    if (neg) swap(a, b), cost = -cost;
    es.push_back({a, sz(f.g[a]), lo, hi, neg});
    f.addEdge(a, b, hi - lo, cost);
    return sz(es) - 1;
  }
  ll solve() {
    ll need = 0;
    rep(v, 0, n) {
      ll s = sup[v];
      if (s > 0) f.addEdge(n, v, s, 0), need += s;
      if (s < 0) f.addEdge(v, n + 1, -s, 0);
    }
    auto [fl, co] = f.flow(n, n + 1);
    return fl < need ? LLONG_MAX : base + co;
  }
  ll flow(int i) {
    auto [a, j, lo, hi, neg] = es[i];
    ll moved = hi - lo - f.g[a][j].cap;
    return neg ? hi - moved : lo + moved;
  }
};
