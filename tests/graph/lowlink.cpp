#include "graph/lowlink.h"
#include "testlib.h"
#include "common_graph.h"
int main() {
  rep(it, 0, 1000) {
    int n = rnd(1, 9), m = rnd(0, 14);
    auto es = rgraph(n, m, true);
    Lowlink L(n, es);
    int base = components(n, es);
    rep(e, 0, m) {
      bool br = es[e].first != es[e].second && components(n, es, e) > base;
      CHECK(L.bridge[e] == br, "edge %d", e);
    }
    rep(v, 0, n) {
      bool isolated = true;
      for (auto [a, b] : es) if ((a == v) != (b == v)) isolated = false;
      bool cut = !isolated && components(n, es, -1, v) > base;
      CHECK(L.cut[v] == cut, "vertex %d", v);
    }
    // bcc: partition of non-loop edges; each is biconnected
    vi seen(m);
    for (auto& comp : L.bcc) {
      set<int> vs;
      for (int e : comp) seen[e]++, vs.insert(es[e].first), vs.insert(es[e].second);
      if (sz(comp) == 1) continue;
      for (int x : vs) {  // removing x keeps the rest of the component connected
        vector<pii> sub;
        for (int e : comp) sub.push_back(es[e]);
        CHECK(components(n, sub, -1, x) == n - 1 - (sz(vs) - 1) + 1);
      }
    }
    rep(e, 0, m) CHECK(seen[e] == (es[e].first != es[e].second));
  }
}
