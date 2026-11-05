#include "graph/spfa.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {  // spfa vs Bellman-Ford
    int n = rnd(1, 8), m = rnd(0, 16), src = rnd(0, n - 1);
    vector<vector<pii>> g(n);
    vector<array<int, 3>> es;
    for (auto [u, v] : rgraph(n, m, true)) {
      int w = rnd(-3, 10);
      g[u].push_back({v, w}), es.push_back({u, v, w});
    }
    const ll INF = LLONG_MAX;
    vector<ll> bf(n, INF);
    bf[src] = 0;
    rep(r, 0, n - 1) for (auto [u, v, w] : es)
      if (bf[u] != INF && bf[u] + w < bf[v]) bf[v] = bf[u] + w;
    bool neg = false;
    for (auto [u, v, w] : es)
      if (bf[u] != INF && bf[u] + w < bf[v]) neg = true;
    auto [d, cyc] = spfa(g, src);
    CHECK(cyc == neg);
    if (!cyc) CHECK(d == bf);
  }
}
