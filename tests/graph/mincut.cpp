#include "graph/mincut.h"
#include "testlib.h"
int main() {
  rep(it, 0, 1500) {
    int n = rnd(2, 9), m = rnd(0, 20);
    vector<vector<ll>> g(n, vector<ll>(n));
    vector<array<ll, 3>> es;
    for (auto [a, b] : rgraph(n, m)) {
      ll w = rnd(0, 10);
      g[a][b] += w, g[b][a] += w, es.push_back({a, b, w});
    }
    // brute force: cut value of every bipartition
    auto cutOf = [&](int mask) {
      ll c = 0;
      for (auto [a, b, w] : es) if ((mask >> a & 1) != (mask >> b & 1)) c += w;
      return c;
    };
    ll best = LLONG_MAX;
    vector<vector<ll>> pair_(n, vector<ll>(n, LLONG_MAX));
    rep(mask, 1, (1 << n) - 1) {
      ll c = cutOf(mask);
      best = min(best, c);
      rep(a, 0, n) rep(b, 0, n) if ((mask >> a & 1) != (mask >> b & 1)) pair_[a][b] = min(pair_[a][b], c);
    }
    auto [c, side] = minCut(g);
    CHECK(c == best, "it=%d got %lld want %lld", it, c, best);
    CHECK(sz(side) >= 1 && sz(side) < n);
    int mask = 0;
    for (int v : side) mask |= 1 << v;
    CHECK(__builtin_popcount(mask) == sz(side) && cutOf(mask) == c);
    // Gomory-Hu: min over the tree path equals the pairwise min cut
    auto tree = gomoryHu(n, es);
    CHECK(sz(tree) == n - 1);
    vector<vector<pair<int, ll>>> t(n);
    for (auto [a, b, w] : tree) t[a].push_back({(int)b, w}), t[b].push_back({(int)a, w});
    rep(a, 0, n) {
      vector<ll> mn(n, -1);
      mn[a] = LLONG_MAX;
      vi st{a};
      while (sz(st)) {
        int v = st.back(); st.pop_back();
        for (auto [u, w] : t[v]) if (mn[u] < 0) mn[u] = min(mn[v], w), st.push_back(u);
      }
      rep(b, 0, n) if (b != a) CHECK(mn[b] == pair_[a][b], "it=%d a=%d b=%d", it, a, b);
    }
  }
}
