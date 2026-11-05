#include "graph/lca.h"
#include "graph/virtualtree.h"
#include "graph/centroid.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 60), root = rnd(0, n - 1);
    auto g = rtree(n);
    vi par(n, -1), dep(n);
    {
      vi st{root}, seen(n);
      seen[root] = 1;
      while (sz(st)) {
        int v = st.back(); st.pop_back();
        for (int u : g[v]) if (!seen[u]) seen[u] = 1, par[u] = v, dep[u] = dep[v] + 1, st.push_back(u);
      }
    }
    auto naive = [&](int a, int b) {
      while (a != b) dep[a] > dep[b] ? a = par[a] : b = par[b];
      return a;
    };
    LCA l(g, root);
    HLD h(g, root);
    vector<ll> val = rvec(n, -100, 100);
    rep(q, 0, 100) {
      int a = rnd(0, n - 1), b = rnd(0, n - 1), c = naive(a, b);
      CHECK(l.lca(a, b) == c && h.lca(a, b) == c);
      CHECK(l.dist(a, b) == dep[a] + dep[b] - 2 * dep[c]);
      for (bool edges : {false, true}) {
        ll want = 0;
        for (int x = a; x != c; x = par[x]) want += val[x];
        for (int x = b; x != c; x = par[x]) want += val[x];
        if (!edges) want += val[c];
        vector<ll> at(n);
        rep(v, 0, n) at[h.pos[v]] = val[v];
        ll got = 0;
        h.path(a, b, [&](int lo, int hi) { rep(i, lo, hi) got += at[i]; }, edges);
        CHECK(got == want);
      }
      // subtree range
      int v = rnd(0, n - 1);
      int cnt = 0;
      rep(u, 0, n) {
        bool inside = naive(u, v) == v;
        cnt += inside;
        CHECK(inside == (h.pos[v] <= h.pos[u] && h.pos[u] < h.pos[v] + h.siz[v]));
      }
      CHECK(cnt == h.siz[v]);
    }
    // virtual tree vs closure under LCA
    rep(q, 0, 30) {
      int k = rnd(1, n);
      vi vs;
      rep(i, 0, k) vs.push_back(rnd(0, n - 1));
      set<int> S(all(vs));
      for (int a : vs) for (int b : vs) S.insert(naive(a, b));
      auto vt = virtualTree(h, vs);
      set<int> got;
      for (auto [v, p] : vt) got.insert(v);
      CHECK(got == S);
      for (auto [v, p] : vt) {
        int want = -1;
        for (int x = par[v]; x >= 0; x = par[x]) if (S.count(x)) { want = x; break; }
        CHECK(p == want);
      }
    }
    // centroid: paths with at most K edges
    int K = rnd(0, n);
    ll want = 0;
    rep(a, 0, n) rep(b, a + 1, n) want += dep[a] + dep[b] - 2 * dep[naive(a, b)] <= K;
    CHECK(pathsUpTo(g, K) == want);
    Centroid cd(g);
    vi order;
    cd.build([&](int c) { order.push_back(c); });
    CHECK(sz(order) == n);
    // centroid tree depth is logarithmic
    rep(v, 0, n) {
      int d = 0;
      for (int x = v; x >= 0; x = cd.cpar[x]) ++d;
      CHECK(d <= __lg(n) + 2);
    }
  }
}
