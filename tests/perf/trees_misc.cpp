// Performance: amortized or randomized structures (splay trees, skew heaps,
// path compression without union by rank, kinetic trees, Pollard rho,
// randomized incremental MEC, palindromic series links).
#include "graph/linkcut.h"
#include "graph/dmst.h"
#include "graph/dominator.h"
#include "data-structures/kst.h"
#include "number-theory/pollard.h"
#include "geometry/point.h"
#include "geometry/circles.h"
#include "strings/eertree.h"
#include "testlib.h"
int main() {
  ll check = 0;
  PERF("link-cut: 2e5 vertices, 5e5 random operations", 1500) {
    int n = 200000;
    LCT t(n);
    vector<pii> edges;
    rep(i, 1, n) {  // a random tree, then random cut + relink keeps it a tree
      int p = rnd(0, i - 1);
      t.link(i, p), edges.push_back({i, p});
    }
    rep(op, 0, 500000) {
      int u = rnd(0, n - 1), v = rnd(0, n - 1), ty = rnd(0, 3);
      if (ty == 0) {
        int i = rnd(0, n - 2);
        auto [a, b] = edges[i];
        t.cut(a, b);
        int c = rnd(0, n - 1);
        while (t.connected(a, c)) c = rnd(0, n - 1);
        t.link(a, c), edges[i] = {a, c};
      } else if (ty == 1) t.update(u, v, rnd(1, 100));
      else if (ty == 2) check += t.query(u, v);
      else check += t.lca(u, v, rnd(0, n - 1));
    }
  }
  PERF("link-cut: path of 2e5, queries between far ends", 400) {
    int n = 200000;
    LCT t(n);
    rep(i, 1, n) t.link(i - 1, i);
    rep(op, 0, 300000) {
      int u = rnd(0, 100), v = rnd(n - 100, n - 1);
      if (op % 2) t.update(u, v, 1);
      else check += t.query(u, v);
    }
  }
  PERF("directed MST: V = 2e5, E = 5e5", 200) {
    int n = 200000;
    vector<Arc> es;
    rep(v, 1, n) es.push_back({rnd(0, v - 1), v, rnd(0, 1e9)});
    rep(i, 0, 500000 - (n - 1)) es.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1), rnd(0, 1e9)});
    auto [cost, par] = dmst(n, 0, es);
    CHECK(cost >= 0);
    check += cost;
  }
  PERF("directed MST: V = 2e5, many cycles (cheap back edges)", 300) {
    int n = 200000;
    vector<Arc> es;
    rep(v, 1, n) es.push_back({v - 1, v, (ll)1e9}), es.push_back({v, v - 1, 1});
    rep(i, 0, 200000) es.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1), rnd(1, 1e6)});
    check += dmst(n, 0, es).first;
  }
  PERF("dominator tree: V = 2e5, E = 5e5 random", 200) {
    int n = 200000;
    vector<vi> g(n);
    rep(v, 1, n) g[rnd(0, v - 1)].push_back(v);
    rep(i, 0, 300000) g[rnd(0, n - 1)].push_back(rnd(0, n - 1));
    auto id = dominators(g, 0);
    check += id[n - 1];
  }
  PERF("dominator tree: path of 1e5 with back edges", 200) {
    int n = 100000;
    vector<vi> g(n);
    rep(v, 1, n) g[v - 1].push_back(v), g[v].push_back(rnd(0, v - 1));
    check += dominators(g, 0)[n - 1];
  }
  PERF("kinetic seg tree: 2e5 positions, 2e5 ops", 250) {
    int n = 200000;
    vector<KST::Ln> v(n);
    for (auto& [a, b] : v) a = rnd(-1000, 1000), b = rnd(-1e9, 1e9);
    KST t(v);
    rep(op, 0, 200000) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n), ty = rnd(0, 2);
      if (ty == 0) t.heat(l, r, rnd(0, 1000));
      else if (ty == 1) t.set(l, {rnd(-1000, 1000), rnd(-1e9, 1e9)});
      else check += t.query(l, r);
    }
  }
  PERF("kinetic seg tree: the leader changes at every heat", 200) {
    int n = 200000;  // i t - i(i-1)/2 is largest at i = t: t += 1 moves it
    vector<KST::Ln> v(n);
    rep(i, 0, n) v[i] = {i, -(ll)i * (i - 1) / 2};
    KST t(v);
    rep(op, 0, n - 1) t.heat(0, n, 1), check += t.query(0, n) % 1000;
  }
  PERF("pollard rho: 200 semiprimes of two ~31-bit primes", 600) {
    auto randPrime = [](ull lo, ull hi) {
      ull p;
      do p = rnd(lo, hi); while (!isPrime(p));
      return p;
    };
    rep(i, 0, 200) {
      ull p = randPrime(1ULL << 30, 1ULL << 31), q = randPrime(1ULL << 30, 1ULL << 31);
      auto f = factor(p * q);
      CHECK(sz(f) == 2 && f[0] * f[1] == p * q);
    }
  }
  // n > 2^63: x^2 + c must not overflow 2^64 (it used to, making rho crawl)
  PERF("pollard rho: 200 semiprimes above 2^63", 800) {
    rep(i, 0, 200) {
      ull p, q;
      do p = rnd(1ULL << 31, (1ULL << 32) - 1); while (!isPrime(p));
      do q = rnd(((1ULL << 63) / p) + 1, (1ULL << 32) - 1); while (!isPrime(q));
      CHECK(p * q > (1ULL << 63) && sz(factor(p * q)) == 2);
    }
  }
  PERF("pollard rho: 2000 random 64-bit numbers", 300) {
    rep(i, 0, 2000) {
      ull x = trng() | 1;
      ull prod = 1;
      for (ull f : factor(x)) prod *= f;
      CHECK(prod == x);
    }
  }
  PERF("minimum enclosing circle: 1e6 random points", 200) {
    vector<Pd> v(1000000);
    for (auto& p : v) p = {rndd(-1e6, 1e6), rndd(-1e6, 1e6)};
    check += (ll)mec(v).second;
  }
  PERF("minimum enclosing circle: 2e5 points on a circle", 200) {
    vector<Pd> v(200000);
    rep(i, 0, sz(v)) v[i] = {cos(i * 1e-5), sin(i * 1e-5)};
    check += (ll)(mec(v).second * 1000);
  }
  PERF("eertree: min palindrome split, 1e6 x 'a'", 200) {
    CHECK(minPalSplit(string(1000000, 'a')) == 1);
  }
  PERF("eertree: min palindrome split, 1e6 random 'ab'", 200) {
    check += minPalSplit(rstr(1000000, 'a', 'b'));
  }
  printf("checksum %lld\n", check);
}
