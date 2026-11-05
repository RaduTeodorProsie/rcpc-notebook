#include "graph/twosat.h"
#include "testlib.h"
int main() {
  rep(it, 0, 500) {  // SCC: same component iff mutually reachable; reverse topo ids
    int n = rnd(1, 12);
    vector<vi> g(n);
    for (auto [a, b] : rgraph(n, rnd(0, 30), true)) g[a].push_back(b);
    vector<vector<bool>> R(n, vector<bool>(n));
    rep(v, 0, n) {
      R[v][v] = true;
      vi st{v};
      while (sz(st)) {
        int x = st.back(); st.pop_back();
        for (int y : g[x]) if (!R[v][y]) R[v][y] = true, st.push_back(y);
      }
    }
    SCC s(g);
    rep(a, 0, n) rep(b, 0, n) {
      CHECK((s.comp[a] == s.comp[b]) == (R[a][b] && R[b][a]));
      if (R[a][b] && s.comp[a] != s.comp[b]) CHECK(s.comp[a] > s.comp[b]);
    }
  }
  rep(it, 0, 1000) {
    int n = rnd(1, 8), m = rnd(0, 20);
    TwoSat ts(n);
    vector<pii> cl;
    rep(i, 0, m) {
      int a = rnd(0, n - 1), b = rnd(0, n - 1);
      if (rnd(0, 1)) a = ~a;
      if (rnd(0, 1)) b = ~b;
      ts.either(a, b), cl.push_back({a, b});
    }
    auto lit = [](int x, int mask) { return x < 0 ? !(mask >> ~x & 1) : (mask >> x & 1); };
    bool want = false;
    rep(mask, 0, 1 << n) {
      bool ok = true;
      for (auto [a, b] : cl) ok &= lit(a, mask) || lit(b, mask);
      want |= ok;
    }
    vi val;
    bool got = ts.solve(val);
    CHECK(got == want);
    if (got) {
      int mask = 0;
      rep(i, 0, n) mask |= val[i] << i;
      for (auto [a, b] : cl) CHECK(lit(a, mask) || lit(b, mask));
    }
  }
}
