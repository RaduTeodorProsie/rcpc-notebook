#include "graph/euler.h"
#include "testlib.h"
int main() {
  rep(it, 0, 6000) {
    int n = rnd(1, 5), m = rnd(0, 7);
    bool directed = rnd(0, 1);
    auto es = rgraph(n, m, true);
    // brute: from each start, try all edge orders and orientations
    auto exists = [&](int src) {
      bool found = false;
      vi used(m);
      function<void(int, int)> go = [&](int v, int k) {
        if (found) return;
        if (k == m) { found = true; return; }
        rep(i, 0, m) if (!used[i]) {
          auto [a, b] = es[i];
          used[i] = 1;
          if (a == v) go(b, k + 1);
          if (!directed && b == v) go(a, k + 1);
          used[i] = 0;
        }
      };
      go(src, 0);
      return found;
    };
    auto valid = [&](const vi& p, int src) {
      CHECK(sz(p) == m + 1, "it=%d", it);
      if (src >= 0) CHECK(p[0] == src, "it=%d", it);
      multiset<pii> left;
      for (auto [a, b] : es) left.insert(directed ? pii{a, b} : pii{min(a, b), max(a, b)});
      rep(i, 0, m) {
        int a = p[i], b = p[i + 1];
        pii e = directed ? pii{a, b} : pii{min(a, b), max(a, b)};
        CHECK(left.count(e), "it=%d", it);
        left.erase(left.find(e));
      }
    };
    bool any = false;
    rep(src, 0, n) {  // a given start
      bool want = exists(src);
      any |= want;
      auto p = eulerPath(n, es, directed, src);
      CHECK(!p.empty() == want, "it=%d src=%d", it, src);
      if (want) valid(p, src);
    }
    auto p = eulerPath(n, es, directed);  // start picked automatically
    CHECK(!p.empty() == any, "it=%d auto", it);
    if (any) valid(p, -1);
  }
}
