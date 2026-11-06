#include "graph/dominator.h"
#include "graph/dmst.h"
#include "testlib.h"
// vertices reachable from s in g without vertex `ban`
vector<bool> reach(const vector<vi>& g, int s, int ban) {
  vector<bool> r(sz(g));
  if (s == ban) return r;
  vi st{s};
  r[s] = 1;
  while (sz(st)) {
    int v = st.back(); st.pop_back();
    for (int u : g[v]) if (u != ban && !r[u]) r[u] = 1, st.push_back(u);
  }
  return r;
}
int main() {
  rep(it, 0, 3000) {  // dominators vs brute force
    int n = rnd(1, 12), m = rnd(0, 3 * n), s = rnd(0, n - 1);
    vector<vi> g(n);
    for (auto [a, b] : rgraph(n, m, true)) g[a].push_back(b);
    auto idom = dominators(g, s);
    auto R = reach(g, s, -1);
    // dom[v] = set of strict dominators
    vector<vi> dom(n);
    rep(u, 0, n) if (u != s) {
      auto r = reach(g, s, u);
      rep(v, 0, n) if (v != u && R[v] && !r[v]) dom[v].push_back(u);
    }
    rep(v, 0, n) if (R[v] && v != s) dom[v].push_back(s);
    rep(v, 0, n) {
      if (!R[v]) { CHECK(idom[v] == -1); continue; }
      if (v == s) { CHECK(idom[v] == s); continue; }
      // idom: the strict dominator that every other strict dominator dominates
      int want = -1;
      for (int d : dom[v]) {
        bool ok = true;
        for (int e : dom[v]) if (e != d && !count(all(dom[d]), e)) ok = false;
        if (ok) want = d;
      }
      CHECK(idom[v] == want, "it=%d v=%d got %d want %d", it, v, idom[v], want);
    }
  }
  {  // long chain: would overflow the stack if the DFS or DSU recursed
    int n = 200000;
    vector<vi> g(n);
    rep(i, 1, n) g[i - 1].push_back(i), g[i].push_back(i - 1);
    auto idom = dominators(g, 0);  // a path: each vertex is dominated by the previous one
    rep(v, 1, n) CHECK(idom[v] == v - 1);
    g[0].push_back(n - 1);  // a ring entered from both ends: only 0 dominates
    idom = dominators(g, 0);
    rep(v, 0, n) CHECK(idom[v] == 0);
  }
  rep(it, 0, 3000) {  // directed MST vs brute force over all parent choices
    int n = rnd(1, 7), m = rnd(0, 14), r = rnd(0, n - 1);
    vector<Arc> es;
    for (auto [a, b] : rgraph(n, m, true)) es.push_back({a, b, rnd(-5, 20)});
    ll want = LLONG_MAX;
    vector<vi> into(n);
    rep(i, 0, sz(es)) if (es[i].b != r && es[i].a != es[i].b) into[es[i].b].push_back(i);
    vi pick(n, -1);
    auto rec = [&](auto& self, int v) -> void {
      if (v == n) {
        ll c = 0;
        vi par(n, -1);
        rep(u, 0, n) if (u != r) par[u] = es[pick[u]].a, c += es[pick[u]].w;
        rep(u, 0, n) {  // every vertex must reach r following parents
          int x = u, steps = 0;
          while (x != r && steps <= n) x = par[x], ++steps;
          if (x != r) return;
        }
        want = min(want, c);
        return;
      }
      if (v == r) return self(self, v + 1);
      for (int i : into[v]) pick[v] = i, self(self, v + 1);
    };
    rec(rec, 0);
    auto [cost, par] = dmst(n, r, es);
    if (want == LLONG_MAX) {
      CHECK(cost == -1 && par.empty(), "it=%d", it);
      continue;
    }
    CHECK(cost == want, "it=%d got %lld want %lld", it, cost, want);
    CHECK(sz(par) == n && par[r] == -1);
    ll c = 0;  // par must be a valid arborescence of that cost using existing edges
    rep(u, 0, n) if (u != r) {
      ll best = LLONG_MAX;
      for (auto e : es) if (e.a == par[u] && e.b == u) best = min(best, e.w);
      CHECK(best != LLONG_MAX, "it=%d u=%d par=%d", it, u, par[u]);
      c += best;
      int x = u, steps = 0;
      while (x != r && steps <= n) x = par[x], ++steps;
      CHECK(x == r);
    }
    CHECK(c == want);
  }
  {  // larger: compare with the O(nm) contraction algorithm
    rep(it, 0, 30) {
      int n = rnd(2, 300), m = rnd(n, 5 * n), r = rnd(0, n - 1);
      vector<Arc> es;
      rep(v, 0, n) if (v != r) es.push_back({(int)rnd(0, n - 1), v, rnd(0, 1e9)});
      for (auto [a, b] : rgraph(n, m, true)) es.push_back({a, b, rnd(0, 1e9)});
      auto naive = [&]() -> ll {  // Chu-Liu/Edmonds, O(nm)
        vector<Arc> E = es;
        int N = n, root = r;
        ll res = 0;
        while (true) {
          vector<ll> in(N, LLONG_MAX);
          vi pre(N, -1), id(N, -1), vis(N, -1);
          for (auto e : E) if (e.a != e.b && e.w < in[e.b]) in[e.b] = e.w, pre[e.b] = e.a;
          rep(v, 0, N) if (v != root && in[v] == LLONG_MAX) return -1;
          int cnt = 0;
          in[root] = 0;
          rep(v, 0, N) {
            res += in[v];
            int x = v;
            while (vis[x] != v && id[x] == -1 && x != root) vis[x] = v, x = pre[x];
            if (x != root && id[x] == -1) {
              for (int y = pre[x]; y != x; y = pre[y]) id[y] = cnt;
              id[x] = cnt++;
            }
          }
          if (!cnt) return res;
          rep(v, 0, N) if (id[v] == -1) id[v] = cnt++;
          for (auto& e : E) {
            int b = e.b;
            e.a = id[e.a], e.b = id[e.b];
            if (e.a != e.b) e.w -= in[b];
          }
          N = cnt, root = id[root];
        }
      };
      auto [cost, par] = dmst(n, r, es);
      CHECK(cost == naive());
    }
  }
}
