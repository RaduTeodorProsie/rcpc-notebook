#include "data-structures/lichao.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {
    int lo = rnd(-100, 100), hi = lo + rnd(1, 200);
    LiChao t(lo, hi);
    vector<Line> ls;
    rep(q, 0, 200) {
      if (rnd(0, 1)) {
        Line l{rnd(-1e6, 1e6), rnd(-1e9, 1e9)};
        t.add(l), ls.push_back(l);
      }
      ll x = rnd(lo, hi - 1), w = LLONG_MIN / 2;
      for (auto& l : ls) w = max(w, l(x));
      CHECK(t.query(x) == w);
    }
  }
}
