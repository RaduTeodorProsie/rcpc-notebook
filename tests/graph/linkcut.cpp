#include "graph/linkcut.h"
#include "testlib.h"
int main() {
  rep(test, 0, 300) {
    int n = rnd(1, 25);
    LCT t(n);
    vector<set<int>> adj(n);
    vector<ll> val(n);
    // path from a to b in the brute-force forest, or empty if not connected
    auto path = [&](int a, int b) {
      vi par(n, -2);
      par[a] = -1;
      queue<int> q({a});
      while (sz(q)) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) if (par[u] == -2) par[u] = v, q.push(u);
      }
      vi p;
      if (par[b] == -2) return p;
      for (int v = b; v != -1; v = par[v]) p.push_back(v);
      return p;
    };
    vector<pii> edges;
    rep(op, 0, 600) {
      int ty = rnd(0, 6), u = rnd(0, n - 1), v = rnd(0, n - 1);
      auto p = path(u, v);
      CHECK(t.connected(u, v) == !p.empty());
      if (ty == 0 && p.empty()) {
        t.link(u, v), adj[u].insert(v), adj[v].insert(u), edges.push_back({u, v});
      } else if (ty == 1 && sz(edges)) {
        int i = rnd(0, sz(edges) - 1);
        auto [a, b] = edges[i];
        if (rnd(0, 1)) swap(a, b);
        t.cut(a, b), adj[a].erase(b), adj[b].erase(a);
        edges.erase(edges.begin() + i);
      } else if (ty == 2 && sz(p)) {
        ll want = 0;
        for (int x : p) want += val[x];
        CHECK(t.query(u, v) == want, "test %d op %d", test, op);
      } else if (ty == 3 && sz(p)) {
        ll a = rnd(-100, 100);
        for (int x : p) val[x] += a;
        t.update(u, v, a);
      } else if (ty == 4 && sz(p)) {
        int r = rnd(0, n - 1);
        if (path(r, u).empty()) continue;
        auto pu = path(r, u), pv = path(r, v);  // r ... at the back
        reverse(all(pu)), reverse(all(pv));
        int i = 0;
        while (i + 1 < sz(pu) && i + 1 < sz(pv) && pu[i + 1] == pv[i + 1]) ++i;
        CHECK(t.lca(u, v, r) == pu[i], "test %d op %d", test, op);
      } else if (ty == 5) {
        ll want = 0;
        for (int x : path(u, u)) want += val[x];
        CHECK(t.query(u, u) == want);
      }
    }
    // final check of every value through single-vertex queries
    rep(v, 0, n) CHECK(t.query(v, v) == val[v]);
  }
  rep(test, 0, 40) {  // many reroots between connectivity checks: lazy reversals deep in splay trees
    int n = rnd(2, 80);
    LCT t(n);
    vi comp(n);
    iota(all(comp), 0);
    vector<pii> edges;
    auto relabel = [&]() {  // components from the edge list
      vector<vi> g(n);
      for (auto [a, b] : edges) g[a].push_back(b), g[b].push_back(a);
      fill(all(comp), -1);
      rep(s, 0, n) if (comp[s] < 0) {
        vi st{s};
        comp[s] = s;
        while (sz(st)) {
          int v = st.back(); st.pop_back();
          for (int u : g[v]) if (comp[u] < 0) comp[u] = s, st.push_back(u);
        }
      }
    };
    rep(op, 0, 3000) {
      int u = rnd(0, n - 1), v = rnd(0, n - 1);
      if (comp[u] != comp[v] && rnd(0, 2)) t.link(u, v), edges.push_back({u, v}), relabel();
      else if (sz(edges) && !rnd(0, 3)) {
        int i = rnd(0, sz(edges) - 1);
        t.cut(edges[i].first, edges[i].second);
        edges.erase(edges.begin() + i), relabel();
      } else if (comp[u] == comp[v]) t.query(u, v);  // a reroot at u
      rep(k, 0, 3) {
        int a = rnd(0, n - 1), b = rnd(0, n - 1);
        CHECK(t.connected(a, b) == (comp[a] == comp[b]), "test %d op %d", test, op);
      }
    }
  }
  {  // long path: deep splay trees and large values, no recursion problems
    int n = 200000;
    LCT t(n);
    rep(i, 1, n) t.link(i - 1, i);
    t.update(0, n - 1, 1000000);
    CHECK(t.query(0, n - 1) == 1000000LL * n);
    CHECK(t.query(n / 2, n / 3) == 1000000LL * (n / 2 - n / 3 + 1));
    CHECK(t.lca(n - 1, n / 2, 0) == n / 2 && t.lca(10, 20, n - 1) == 20);
    t.cut(n / 2, n / 2 + 1);
    CHECK(!t.connected(0, n - 1) && t.connected(0, n / 2));
  }
}
