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
  rep(it, 0, 2000) {  // 2-SAT with every constraint type vs brute force
    int n = rnd(1, 7), m = rnd(0, 12);
    TwoSat ts(n);
    auto lit = [](int x, int mask) { return x < 0 ? !(mask >> ~x & 1) : (mask >> x & 1); };
    auto rl = [&]() { int x = rnd(0, n - 1); return rnd(0, 1) ? ~x : x; };
    vector<function<bool(int)>> cons;
    rep(i, 0, m) {
      int ty = rnd(0, 5), a = rl(), b = rl();
      if (ty == 0) ts.either(a, b), cons.push_back([=](int k) { return lit(a, k) || lit(b, k); });
      if (ty == 1) ts.implies(a, b), cons.push_back([=](int k) { return !lit(a, k) || lit(b, k); });
      if (ty == 2) ts.force(a), cons.push_back([=](int k) { return lit(a, k); });
      if (ty == 3) ts.same(a, b), cons.push_back([=](int k) { return lit(a, k) == lit(b, k); });
      if (ty == 4) ts.differ(a, b), cons.push_back([=](int k) { return lit(a, k) != lit(b, k); });
      if (ty == 5) {
        vi li(rnd(0, 4));
        for (int& x : li) x = rl();
        ts.atMostOne(li);
        cons.push_back([=](int k) { int c = 0; for (int x : li) c += lit(x, k); return c <= 1; });
      }
    }
    bool want = false;
    rep(mask, 0, 1 << n) {
      bool ok = true;
      for (auto& c : cons) ok &= c(mask);
      want |= ok;
    }
    vi val;
    bool got = ts.solve(val);
    CHECK(got == want, "it=%d", it);
    if (got) {
      int mask = 0;
      rep(i, 0, n) mask |= val[i] << i;
      for (auto& c : cons) CHECK(c(mask));
    }
  }
}
