#include "graph/mincirc.h"
#include "graph/dinic.h"
#include "testlib.h"
int main() {
  // Random small networks with lower bounds, supplies and costs of any
  // sign (negative cycles included), against brute force over all flows.
  int feasible = 0;
  rep(it, 0, 3000) {
    int n = rnd(1, 4), m = rnd(0, 6);
    vector<array<ll, 5>> es;
    rep(i, 0, m) {
      ll lo = rnd(0, 2), hi = lo + rnd(0, 2);
      if (rnd(0, 3) == 0) lo = 0;
      es.push_back({rnd(0, n - 1), rnd(0, n - 1), lo, hi, rnd(-5, 5)});
    }
    vector<ll> sup(n);
    if (n > 1 && rnd(0, 1)) {
      ll s = rnd(1, 2);
      int a = rnd(0, n - 1), b = rnd(0, n - 1);
      sup[a] += s, sup[b] -= s;
    }
    MinCirc g(n);
    rep(v, 0, n) g.sup[v] += sup[v];
    for (auto [a, b, lo, hi, c] : es) g.addEdge(a, b, lo, hi, c);
    ll got = g.solve();
    ll best = LLONG_MAX;
    vector<ll> x(m);
    function<void(int)> go = [&](int i) {
      if (i == m) {
        vector<ll> bal = sup;  // produced + inflow - outflow must be 0
        ll c = 0;
        rep(j, 0, m) bal[es[j][0]] -= x[j], bal[es[j][1]] += x[j], c += x[j] * es[j][4];
        rep(v, 0, n) if (bal[v]) return;
        best = min(best, c);
        return;
      }
      for (x[i] = es[i][2]; x[i] <= es[i][3]; ++x[i]) go(i + 1);
    };
    go(0);
    CHECK(got == best, "it=%d got %lld want %lld", it, got, best);
    if (got == LLONG_MAX) continue;
    ++feasible;
    vector<ll> bal = sup;
    ll c = 0;
    rep(j, 0, m) {
      ll fl = g.flow(j);
      CHECK(es[j][2] <= fl && fl <= es[j][3], "it=%d edge %d flow %lld", it, j, fl);
      bal[es[j][0]] -= fl, bal[es[j][1]] += fl, c += fl * es[j][4];
    }
    rep(v, 0, n) CHECK(bal[v] == 0, "it=%d not balanced", it);
    CHECK(c == got, "it=%d flows cost %lld", it, c);
  }
  CHECK(feasible > 1000, "only %d feasible cases", feasible);
  // Min-cost max s-t flow with negative cycles, as in the description.
  rep(it, 0, 1500) {
    int n = rnd(2, 4), m = rnd(1, 6);
    int s = 0, t = n - 1;
    vector<array<ll, 4>> es;
    rep(i, 0, m) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(0, 2), rnd(-5, 5)});
    Dinic d(n);
    for (auto [a, b, cap, c] : es) d.addEdge(a, b, cap);
    ll F = d.flow(s, t);
    MinCirc g(n);
    for (auto [a, b, cap, c] : es) g.addEdge(a, b, 0, cap, c);
    g.addEdge(t, s, F, F, 0);
    ll got = g.solve();
    ll bestF = -1, bestC = 0;
    vector<ll> x(m);
    function<void(int)> go = [&](int i) {
      if (i == m) {
        vector<ll> bal(n);
        ll c = 0;
        rep(j, 0, m) bal[es[j][0]] -= x[j], bal[es[j][1]] += x[j], c += x[j] * es[j][3];
        rep(v, 0, n) if (v != s && v != t && bal[v]) return;
        ll fv = bal[t];
        if (s == t || fv < 0 || bal[s] != -fv) return;
        if (fv > bestF || (fv == bestF && c < bestC)) bestF = fv, bestC = c;
        return;
      }
      for (x[i] = 0; x[i] <= es[i][2]; ++x[i]) go(i + 1);
    };
    go(0);
    CHECK(bestF == F, "it=%d max flow %lld vs %lld", it, F, bestF);
    CHECK(got == bestC, "it=%d got %lld want %lld", it, got, bestC);
  }
}
