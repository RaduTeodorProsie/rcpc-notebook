#include "data-structures/fenwick2d.h"
#include "testlib.h"
int main() {
  rep(it, 0, 1500) {
    int n = rnd(1, 12), q = rnd(1, 60);
    ll Y = it % 2 ? 6 : 2000000000;
    vector<array<ll, 4>> ops;  // type, x, y, v
    rep(i, 0, q) {
      int x = rnd(0, n - 1);
      ll y = rnd(-Y, Y);
      if (rnd(0, 1)) ops.push_back({0, x, y, rnd(-5, 5)});
      else ops.push_back({1, rnd(0, n), y, 0});  // sum: x in [0, n]
    }
    Fenwick2D f(n);
    for (auto [t, x, y, v] : ops) if (t == 0) f.fake(x, y);
    f.init();
    map<pair<ll, ll>, ll> pts;
    for (auto [t, x, y, v] : ops) {
      if (t == 0) f.add(x, y, v), pts[{x, y}] += v;
      else {
        ll want = 0;
        for (auto [p, w] : pts) if (p.first < x && p.second < y) want += w;
        CHECK(f.sum(x, y) == want, "it=%d", it);
      }
    }
    // also query y values never faked, at the extremes
    rep(x, 0, n + 1) for (ll y : {(ll)INT_MIN, (ll)INT_MAX, 0LL}) {
      ll want = 0;
      for (auto [p, w] : pts) if (p.first < x && p.second < y) want += w;
      CHECK(f.sum(x, y) == want);
    }
  }
}
