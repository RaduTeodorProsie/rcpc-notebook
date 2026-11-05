#include "data-structures/rollback.h"
#include "data-structures/dsu.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {  // rollback against rebuilding from scratch
    int n = rnd(1, 30);
    RollbackDSU d(n);
    vector<pii> ops;
    vi times;
    rep(q, 0, 200) {
      int t = rnd(0, 3);
      if (t == 0 && sz(times)) {
        int k = rnd(0, sz(times) - 1);
        d.rollback(times[k]);
        ops.resize(times[k]);
        times.resize(k);
      } else if (t == 1) {
        times.push_back(d.time());
      } else {
        int a = rnd(0, n - 1), b = rnd(0, n - 1);
        if (d.join(a, b)) ops.push_back({a, b});
      }
      DSU ref(n);
      int comps = n;
      for (auto [a, b] : ops) comps -= ref.join(a, b);
      CHECK(d.comps == comps);
      rep(x, 0, n) rep(y, 0, n)
        CHECK((d.find(x) == d.find(y)) == (ref.find(x) == ref.find(y)));
    }
  }
  rep(it, 0, 100) {  // dynamic connectivity
    int n = rnd(1, 15), T = rnd(1, 40), m = rnd(0, 30);
    DynConn dc(T);
    vector<array<int, 4>> es;
    rep(i, 0, m) {
      int l = rnd(0, T - 1), r = rnd(l + 1, T);
      es.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1), l, r});
      dc.addEdge(es[i][0], es[i][1], l, r);
    }
    vi res = dc.run(n);
    rep(t, 0, T) {
      DSU ref(n);
      int comps = n;
      for (auto& e : es) if (e[2] <= t && t < e[3]) comps -= ref.join(e[0], e[1]);
      CHECK(res[t] == comps);
    }
  }
}
