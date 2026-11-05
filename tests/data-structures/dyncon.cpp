#include "data-structures/dyncon.h"
#include "data-structures/dsu.h"
#include "testlib.h"
int main() {
  // edge cases: no events at all, and removing an edge that is not there
  CHECK(fromEvents(0, {}).run(3).empty());
  vi r = fromEvents(3, {{-1, 0, 1}, {1, 0, 1}, {-1, 1, 2}}).run(3);
  CHECK(r == vi({3, 2, 2}));
  rep(it, 0, 300) {
    int n = rnd(1, 12), T = rnd(1, 60);
    vector<array<int, 3>> ev;
    multiset<pii> live;
    vector<multiset<pii>> snap;
    rep(t, 0, T) {
      int ty = rnd(-1, 1), a = rnd(0, n - 1), b = rnd(0, n - 1);
      if (ty < 0) {
        if (live.empty()) ty = 0;
        else {
          auto e = *next(live.begin(), rnd(0, sz(live) - 1));
          a = e.first, b = e.second;
          if (rnd(0, 1)) swap(a, b);
          live.erase(live.find(e));
        }
      }
      if (ty > 0) live.insert(minmax(a, b));
      ev.push_back({ty, a, b});
      snap.push_back(live);
    }
    vi res = fromEvents(T, ev).run(n);
    rep(t, 0, T) {
      DSU d(n);
      int c = n;
      for (auto [a, b] : snap[t]) c -= d.join(a, b);
      CHECK(res[t] == c, "t=%d", t);
    }
  }
}
