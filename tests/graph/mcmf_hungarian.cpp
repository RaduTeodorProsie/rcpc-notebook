#include "graph/mcmf.h"
#include "graph/hungarian.h"
#include "testlib.h"
int main() {
  rep(it, 0, 500) {
    int n = rnd(1, 6), m = rnd(n, 7);
    vector<vector<ll>> a(n, vector<ll>(m));
    for (auto& r : a) for (auto& x : r) x = rnd(-20, 50);
    vi p(m);
    iota(all(p), 0);
    ll best = LLONG_MAX;
    do {
      ll c = 0;
      rep(i, 0, n) c += a[i][p[i]];
      best = min(best, c);
    } while (next_permutation(all(p)));
    auto [cost, match] = hungarian(a);
    CHECK(cost == best);
    ll c = 0;
    set<int> cols;
    rep(i, 0, n) c += a[i][match[i]], cols.insert(match[i]);
    CHECK(c == best && sz(cols) == n);
    MCMF f(n + m + 2);
    int S = n + m, T = S + 1;
    rep(i, 0, n) f.addEdge(S, i, 1, 0);
    rep(j, 0, m) f.addEdge(n + j, T, 1, 0);
    rep(i, 0, n) rep(j, 0, m) f.addEdge(i, n + j, 1, a[i][j]);
    auto [fl, co] = f.flow(S, T);
    CHECK(fl == n && co == best);
  }
  rep(it, 0, 300) {  // min-cost flow with a flow limit, vs brute over flows
    int n = rnd(2, 4), m = rnd(1, 5);
    vector<array<ll, 4>> es;
    rep(i, 0, m) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(0, 2), rnd(0, 6)});
    ll lim = rnd(0, 3);
    MCMF f(n);
    for (auto [a, b, cap, cost] : es) f.addEdge(a, b, cap, cost);
    auto [fl, co] = f.flow(0, n - 1, lim);
    ll bestF = -1, bestC = 0;
    vector<ll> x(m);
    function<void(int)> go = [&](int i) {
      if (i == m) {
        vector<ll> bal(n);
        ll c = 0;
        rep(j, 0, m) bal[es[j][0]] -= x[j], bal[es[j][1]] += x[j], c += x[j] * es[j][3];
        rep(v, 1, n - 1) if (bal[v]) return;
        ll fv = bal[n - 1];
        if (fv < 0 || fv > lim) return;
        if (fv > bestF || (fv == bestF && c < bestC)) bestF = fv, bestC = c;
        return;
      }
      for (x[i] = 0; x[i] <= es[i][2]; ++x[i]) go(i + 1);
    };
    go(0);
    CHECK(fl == bestF && co == bestC, "it=%d got (%lld,%lld) want (%lld,%lld)", it, fl, co, bestF, bestC);
  }
}
