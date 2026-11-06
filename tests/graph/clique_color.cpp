#include "graph/maxclique.h"
#include "graph/edgecolor.h"
#include "testlib.h"
int main() {
  rep(it, 0, 3000) {  // max clique vs brute force over subsets
    int n = rnd(1, 14);
    double p = rndd(0.1, 0.95);
    vector<B> g(n);
    rep(i, 0, n) rep(j, 0, i) if (rndd(0, 1) < p) g[i][j] = g[j][i] = 1;
    int best = 0;
    rep(m, 1, 1 << n) {
      bool ok = true;
      rep(i, 0, n) if (m >> i & 1) rep(j, 0, i) if (m >> j & 1) ok &= g[i][j];
      if (ok) best = max(best, __builtin_popcount(m));
    }
    vi c = MaxClique(g).run();
    CHECK(sz(c) == best, "it=%d got %d want %d", it, sz(c), best);
    set<int> s(all(c));
    CHECK(sz(s) == sz(c));
    for (int a : c) for (int b : c) if (a != b) CHECK(g[a][b], "it=%d not a clique", it);
  }
  {  // planted clique in a big random graph, all 128 bits used
    int n = 128, k = 14;
    vector<B> g(n);
    rep(i, 0, n) rep(j, 0, i) if (rnd(0, 1)) g[i][j] = g[j][i] = 1;
    vi perm(n);
    iota(all(perm), 0);
    shuffle(all(perm), trng);
    rep(i, 0, k) rep(j, 0, i) g[perm[i]][perm[j]] = g[perm[j]][perm[i]] = 1;
    vi c = MaxClique(g).run();
    CHECK(sz(c) >= k);
    for (int a : c) for (int b : c) if (a != b) CHECK(g[a][b]);
  }
  rep(it, 0, 3000) {  // edge colouring: proper, colours in [0, D]
    int n = rnd(1, it < 2000 ? 8 : 60);
    double p = rndd(0, 1);
    vector<pii> es;
    rep(i, 0, n) rep(j, 0, i) if (rndd(0, 1) < p) es.push_back(rnd(0, 1) ? pii{i, j} : pii{j, i});
    shuffle(all(es), trng);
    if (es.empty()) continue;
    vi deg(n);
    for (auto [a, b] : es) deg[a]++, deg[b]++;
    int D = *max_element(all(deg));
    vi col = edgeColor(n, es);
    CHECK(sz(col) == sz(es));
    vector<set<int>> at(n);
    rep(i, 0, sz(es)) {
      CHECK(0 <= col[i] && col[i] <= D, "it=%d colour %d, D=%d", it, col[i], D);
      auto [a, b] = es[i];
      CHECK(at[a].insert(col[i]).second && at[b].insert(col[i]).second, "it=%d clash", it);
    }
  }
}
