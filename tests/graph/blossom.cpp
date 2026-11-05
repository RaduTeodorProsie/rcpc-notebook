#include "graph/blossom.h"
#include "testlib.h"
#include "common_graph.h"
int main() {
  rep(it, 0, 3000) {
    int n = rnd(1, 12), m = rnd(0, 30);
    auto es = rgraph(n, m);
    Blossom b(n);
    for (auto [x, y] : es) b.addEdge(x, y);
    int r = b.solve();
    CHECK(r == bruteMatching(n, es), "it=%d", it);
    int cnt = 0;
    set<pii> E;
    for (auto [x, y] : es) E.insert({x, y}), E.insert({y, x});
    rep(v, 0, n) if (b.match[v] >= 0) {
      CHECK(b.match[b.match[v]] == v && E.count({v, b.match[v]}));
      ++cnt;
    }
    CHECK(cnt == 2 * r);
  }
}
