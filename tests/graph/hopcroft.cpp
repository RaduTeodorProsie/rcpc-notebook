#include "graph/hopcroft.h"
#include "testlib.h"
#include "common_graph.h"
int main() {
  rep(it, 0, 1000) {
    int n = rnd(1, 7), m = rnd(1, 7), e = rnd(0, 20);
    HK h(n, m);
    vector<pii> es, ge;
    rep(i, 0, e) {
      int a = rnd(0, n - 1), b = rnd(0, m - 1);
      h.addEdge(a, b), es.push_back({a, b}), ge.push_back({a, n + b});
    }
    int r = h.run();
    CHECK(r == bruteMatching(n + m, ge));
    int cnt = 0;
    rep(a, 0, n) if (h.ml[a] >= 0) {
      CHECK(h.mr[h.ml[a]] == a);
      ++cnt;
    }
    CHECK(cnt == r);
    auto [L, R] = vertexCover(h);
    CHECK(sz(L) + sz(R) == r);
    set<int> sl(all(L)), sr(all(R));
    for (auto [a, b] : es) CHECK(sl.count(a) || sr.count(b));
  }
}
