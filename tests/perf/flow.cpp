// Performance: flows and matchings. Their worst-case bounds (O(V^2 E),
// O(F E log V), O(V^3)) are far from what they do in practice, so measure.
#include "graph/dinic.h"
#include "graph/mcmf.h"
#include "graph/hopcroft.h"
#include "graph/blossom.h"
#include "graph/mincut.h"
#include "testlib.h"
int main() {
  ll check = 0;
  PERF("dinic: random V = 1e4, E = 1e5, caps <= 1e9", 200) {
    int n = 10000;
    Dinic d(n);
    rep(i, 0, 100000) d.addEdge(rnd(0, n - 1), rnd(0, n - 1), rnd(1, 1e9));
    check += d.flow(0, n - 1);
  }
  PERF("dinic: unit bipartite matching 1e5 + 1e5, E = 5e5", 800) {
    int L = 100000, s = 2 * L, t = s + 1;
    Dinic d(2 * L + 2);
    rep(i, 0, L) d.addEdge(s, i, 1), d.addEdge(L + i, t, 1);
    rep(i, 0, 500000) d.addEdge(rnd(0, L - 1), L + rnd(0, L - 1), 1);
    check += d.flow(s, t);
  }
  PERF("dinic: 300 x 300 grid, random caps", 200) {
    int k = 300;
    Dinic d(k * k);
    rep(i, 0, k) rep(j, 0, k) {
      int v = i * k + j;
      if (i + 1 < k) d.addEdge(v, v + k, rnd(1, 1e6), rnd(1, 1e6));
      if (j + 1 < k) d.addEdge(v, v + 1, rnd(1, 1e6), rnd(1, 1e6));
    }
    check += d.flow(0, k * k - 1);
  }
  PERF("dinic: dense V = 500 (all pairs)", 200) {
    int n = 500;
    Dinic d(n);
    rep(i, 0, n) rep(j, 0, n) if (i != j) d.addEdge(i, j, rnd(1, 1e9));
    check += d.flow(0, n - 1);
  }
  PERF("mcmf: assignment 300 x 300 (flow 300)", 200) {
    int k = 300, s = 2 * k, t = s + 1;
    MCMF f(2 * k + 2);
    rep(i, 0, k) {
      f.addEdge(s, i, 1, 0), f.addEdge(k + i, t, 1, 0);
      rep(j, 0, k) f.addEdge(i, k + j, 1, rnd(0, 1e6));
    }
    auto [fl, co] = f.flow(s, t);
    CHECK(fl == k);
    check += co;
  }
  PERF("mcmf: random V = 2000, E = 2e4, caps <= 10", 200) {
    int n = 2000;
    MCMF f(n);
    rep(i, 0, 20000) f.addEdge(rnd(0, n - 1), rnd(0, n - 1), rnd(1, 10), rnd(0, 10000));
    auto [fl, co] = f.flow(0, n - 1);
    check += fl + co;
  }
  PERF("mcmf: negative-cost DAG V = 2000, E = 2e4", 200) {
    int n = 2000;
    MCMF f(n);
    rep(i, 0, n - 1) f.addEdge(i, i + 1, 50, rnd(-100, 100));
    rep(i, 0, 20000) {
      int a = rnd(0, n - 2), b = rnd(a + 1, n - 1);
      f.addEdge(a, b, rnd(1, 5), rnd(-1000, 1000));
    }
    auto [fl, co] = f.flow(0, n - 1);
    check += fl + co;
  }
  PERF("hopcroft: random 1e5 + 1e5, E = 5e5", 200) {
    int L = 100000;
    HK h(L, L);
    rep(i, 0, 500000) h.addEdge(rnd(0, L - 1), rnd(0, L - 1));
    check += h.run();
  }
  // Left i sees right i and i + 1, added so the first greedy pass matches
  // i to i + 1: the last vertex then needs an augmenting path through all.
  PERF("hopcroft: chain 1e5 (long augmenting path)", 200) {
    int L = 100000;
    HK h(L, L);
    rep(i, 0, L) {
      if (i + 1 < L) h.addEdge(i, i + 1);
      h.addEdge(i, i);
    }
    int r = h.run();
    CHECK(r == L);
    check += r;
  }
  PERF("blossom: random V = 500, E = 5e4", 200) {
    int n = 500;
    Blossom b(n);
    rep(i, 0, 50000) {
      int x = rnd(0, n - 1), y = rnd(0, n - 1);
      if (x != y) b.addEdge(x, y);
    }
    check += b.solve();
  }
  PERF("blossom: sparse V = 4000, E = 8000", 200) {
    int n = 4000;
    Blossom b(n);
    rep(i, 0, 8000) {
      int x = rnd(0, n - 1), y = rnd(0, n - 1);
      if (x != y) b.addEdge(x, y);
    }
    check += b.solve();
  }
  PERF("blossom: odd cycles (triangles in a chain), V = 3000", 200) {
    int n = 3000;
    Blossom b(n);
    for (int i = 0; i + 2 < n; i += 2) b.addEdge(i, i + 1), b.addEdge(i + 1, i + 2), b.addEdge(i, i + 2);
    check += b.solve();
  }
  PERF("gomory-hu: V = 300, E = 3000 (299 flows)", 200) {
    int n = 300;
    vector<array<ll, 3>> es;
    rep(i, 1, n) es.push_back({rnd(0, i - 1), i, rnd(1, 1e6)});
    rep(i, 0, 3000 - (n - 1)) es.push_back({rnd(0, n - 1), rnd(0, n - 1), rnd(1, 1e6)});
    for (auto [a, b, w] : gomoryHu(n, es)) check += w;
  }
  printf("checksum %lld\n", check);
}
