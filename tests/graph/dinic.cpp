#include "graph/dinic.h"
#include "testlib.h"
int main() {
  rep(it, 0, 500) {
    int n = rnd(2, 7), m = rnd(0, 12), s = 0, t = n - 1;
    vector<array<ll, 3>> es;
    rep(i, 0, m) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(0, 5)});
    Dinic d(n);
    for (auto [a, b, c] : es) d.addEdge(a, b, c);
    ll f = d.flow(s, t);
    // brute min cut over all subsets containing s, not t
    ll best = LLONG_MAX;
    rep(mask, 0, 1 << n) if ((mask & 1) && !(mask >> t & 1)) {
      ll c = 0;
      for (auto [a, b, cap] : es) if ((mask >> a & 1) && !(mask >> b & 1)) c += cap;
      best = min(best, c);
    }
    CHECK(f == best);
    auto side = minCut(d);
    ll c = 0;
    for (auto [a, b, cap] : es) if (side[a] && !side[b]) c += cap;
    CHECK(side[s] && !side[t] && c == f);
  }
  rep(it, 0, 500) {  // lower bounds vs brute enumeration
    int n = rnd(2, 4), m = rnd(1, 5), s = 0, t = n - 1;
    vector<array<ll, 4>> es;
    rep(i, 0, m) {
      ll lo = rnd(0, 2), hi = lo + rnd(0, 2);
      es.push_back({rnd(0, n - 1), rnd(0, n - 1), lo, hi});
    }
    bool want = false;
    vector<ll> f(m);
    function<void(int)> go = [&](int i) {
      if (want) return;
      if (i == m) {
        vector<ll> bal(n);
        rep(j, 0, m) bal[es[j][0]] -= f[j], bal[es[j][1]] += f[j];
        bool ok = true;
        rep(v, 0, n) if (v != s && v != t && bal[v]) ok = false;
        if (bal[t] < 0) ok = false;  // net flow goes s -> t
        want |= ok;
        return;
      }
      for (f[i] = es[i][2]; f[i] <= es[i][3]; ++f[i]) go(i + 1);
    };
    go(0);
    CHECK(feasible(n, es, s, t) == want, "it=%d", it);
  }
}
