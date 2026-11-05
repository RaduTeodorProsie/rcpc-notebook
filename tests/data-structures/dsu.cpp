#include "data-structures/dsu.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {
    int n = rnd(1, 60);
    DSU d(n);
    vi comp(n);
    iota(all(comp), 0);
    rep(q, 0, 300) {
      int a = rnd(0, n - 1), b = rnd(0, n - 1);
      bool diff = comp[a] != comp[b];
      CHECK(d.join(a, b) == diff);
      int ca = comp[a], cb = comp[b];
      for (int& c : comp) if (c == cb) c = ca;
      int x = rnd(0, n - 1), s = count(all(comp), comp[x]);
      CHECK(d.size(x) == s);
      int y = rnd(0, n - 1);
      CHECK((d.find(x) == d.find(y)) == (comp[x] == comp[y]));
    }
  }
}
