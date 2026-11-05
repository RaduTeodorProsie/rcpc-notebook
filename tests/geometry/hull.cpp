#include "geometry/hull.h"
#include "geometry/polygon.h"
#include "geometry/closest.h"
#include "geometry/minkowski.h"
#include "testlib.h"
using Pl = P<ll>;
int main() {
  rep(it, 0, 3000) {
    int n = rnd(1, 30), c = rnd(1, 10);
    vector<Pl> pts(n);
    for (auto& p : pts) p = {rnd(-c, c), rnd(-c, c)};
    auto h = hull(pts);
    int k = sz(h);
    set<pair<ll, ll>> in;
    for (auto p : pts) in.insert({p.x, p.y});
    for (auto p : h) CHECK(in.count({p.x, p.y}));
    if (sz(in) == 1) { CHECK(k == 1); continue; }
    CHECK(k >= 2);
    if (k >= 3) rep(i, 0, k) CHECK(h[i].cross(h[(i + 1) % k], h[(i + 2) % k]) > 0);
    for (auto p : pts) rep(i, 0, k) CHECK(h[i].cross(h[(i + 1) % k], p) >= 0);
    // diameter
    ll best = 0;
    for (auto a : pts) for (auto b : pts) best = max(best, (a - b).dist2());
    CHECK(diameter2(h) == best, "it=%d k=%d", it, k);
    if (k >= 3) rep(q, 0, 30) {
      Pl p{rnd(-c - 1, c + 1), rnd(-c - 1, c + 1)};
      CHECK(inConvex(h, p) == (inside(h, p) >= 0));
    }
    if (n >= 2) {
      ll w = LLONG_MAX;
      rep(i, 0, n) rep(j, i + 1, n) w = min(w, (pts[i] - pts[j]).dist2());
      CHECK(closestPair(pts) == w);
    }
    // Minkowski sum vs hull of all pairwise sums
    vector<Pl> q(rnd(1, 10));
    for (auto& p : q) p = {rnd(-c, c), rnd(-c, c)};
    auto h2 = hull(q);
    if (k >= 2 && sz(h2) >= 2) {
      vector<Pl> sums;
      for (auto a : h) for (auto b : h2) sums.push_back(a + b);
      auto want = hull(sums), got = hull(minkowski(h, h2));
      CHECK(want == got);
    }
  }
  vector<Pl> big(100000);
  for (auto& p : big) p = {rnd(-1e9, 1e9), rnd(-1e9, 1e9)};
  closestPair(big);
}
