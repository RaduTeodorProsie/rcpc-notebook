// Performance: maximum clique on random graphs (the timings in its description).
#include "graph/maxclique.h"
#include "testlib.h"
int main() {
  int r = 0;
  PERF("max clique: n = 128, density 0.8, 3 graphs", 400) {
    rep(t, 0, 3) {
      vector<B> g(128);
      rep(i, 0, 128) rep(j, 0, i) if (rndd(0, 1) < 0.8) g[i][j] = g[j][i] = 1;
      r += sz(MaxClique(g).run());
    }
  }
  CHECK(r > 0);
}
