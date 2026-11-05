#include "graph/euler.h"
#include "testlib.h"
int main() {
  rep(it, 0, 3000) {
    int n = rnd(1, 5), m = rnd(0, 7), src = rnd(0, n - 1);
    bool directed = rnd(0, 1);
    auto es = rgraph(n, m, true);
    // brute: try all edge orders and orientations
    bool want = false;
    vi used(m);
    function<void(int, int)> go = [&](int v, int k) {
      if (want) return;
      if (k == m) { want = true; return; }
      rep(i, 0, m) if (!used[i]) {
        auto [a, b] = es[i];
        used[i] = 1;
        if (a == v) go(b, k + 1);
        if (!directed && b == v) go(a, k + 1);
        used[i] = 0;
      }
    };
    go(src, 0);
    auto p = eulerPath(n, es, directed, src);
    CHECK(!p.empty() == want, "it=%d", it);
    if (p.empty()) continue;
    CHECK(sz(p) == m + 1 && p[0] == src);
    multiset<pii> left;
    for (auto [a, b] : es) left.insert(directed ? pii{a, b} : pii{min(a, b), max(a, b)});
    rep(i, 0, m) {
      int a = p[i], b = p[i + 1];
      pii e = directed ? pii{a, b} : pii{min(a, b), max(a, b)};
      CHECK(left.count(e));
      left.erase(left.find(e));
    }
  }
}
