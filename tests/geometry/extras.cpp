#include "geometry/angle.h"
#include "geometry/polycut.h"
#include "geometry/tangents.h"
#include "geometry/polycircle.h"
#include "geometry/point3.h"
#include "geometry/manhattanmst.h"
#include "geometry/hull.h"
#include "geometry/polygon.h"
#include "data-structures/dsu.h"
#include "testlib.h"
const double EPS = 1e-6;
bool near(double a, double b, double e = EPS) { return fabs(a - b) <= e * max(1.0, fabs(b)); }
vector<Pd> randConvex(int k, double R) {
  vector<P<ll>> pts;
  rep(i, 0, k) pts.push_back({rnd(-(ll)R, (ll)R), rnd(-(ll)R, (ll)R)});
  vector<P<ll>> h = hull(pts);
  vector<Pd> r;
  for (auto p : h) r.push_back({(double)p.x, (double)p.y});
  return r;
}
int main() {
  {  // angular sort vs atan2
    rep(it, 0, 20000) {
      P<ll> a{rnd(-6, 6), rnd(-6, 6)}, b{rnd(-6, 6), rnd(-6, 6)};
      if (a == P<ll>{0, 0} || b == P<ll>{0, 0}) continue;
      auto ang = [](P<ll> p) {
        double t = atan2((double)p.y, (double)p.x);
        return t < 0 ? t + 2 * M_PI : t;
      };
      double ta = ang(a), tb = ang(b);
      bool same = a.cross(b) == 0 && a.dot(b) > 0;
      if (same) CHECK(angleLess(a, b) == (a.dist2() < b.dist2()));
      else CHECK(angleLess(a, b) == (ta < tb));
    }
  }
  rep(it, 0, 2000) {  // polygon cut
    vector<Pd> poly = randConvex(rnd(3, 10), 10);
    if (sz(poly) < 3) continue;
    Pd p{rndd(-12, 12), rndd(-12, 12)}, q{rndd(-12, 12), rndd(-12, 12)};
    if ((q - p).len() < 1e-3) continue;
    vector<Pd> L = polyCut(poly, p, q), R = polyCut(poly, q, p);
    auto ar = [](const vector<Pd>& v) { return v.empty() ? 0.0 : area2(v) / 2; };
    CHECK(near(ar(L) + ar(R), ar(poly), 1e-9));
    for (Pd x : L) CHECK(p.cross(q, x) >= -1e-6 * (q - p).len());
    CHECK(ar(L) >= -1e-9);
  }
  rep(it, 0, 3000) {  // tangents
    Pd c{rndd(-5, 5), rndd(-5, 5)}, p{rndd(-8, 8), rndd(-8, 8)};
    double r = rndd(0.1, 4);
    auto t = tangents(c, r, p, 0);
    CHECK(sz(t) == ((p - c).len() > r ? 2 : 0));
    for (auto [x, y] : t) {
      CHECK(near((y - p).len(), 0));
      CHECK(near((x - c).len(), r));
      CHECK(fabs((x - c).dot(x - p)) < 1e-6);
    }
  }
  rep(it, 0, 3000) {
    Pd c1{(double)rnd(-5, 5), (double)rnd(-5, 5)}, c2{(double)rnd(-5, 5), (double)rnd(-5, 5)};
    double r1 = rnd(1, 4), r2 = rnd(1, 4), d = (c2 - c1).len();
    for (int inner : {0, 1}) {
      double R2 = inner ? -r2 : r2;
      auto ts = tangents(c1, r1, c2, R2);
      double lim = inner ? r1 + r2 : fabs(r1 - r2);
      int want = d == 0 ? 0 : d * d > lim * lim ? 2 : d * d == lim * lim ? 1 : 0;
      CHECK(sz(ts) == want);
      for (auto [u, v] : ts) {
        CHECK(near((u - c1).len(), r1) && near((v - c2).len(), r2));
        if ((v - u).len() > 1e-9) {
          Pd dir = v - u;
          CHECK(fabs((u - c1).dot(dir)) < 1e-6 && fabs((v - c2).dot(dir)) < 1e-6);
        }
      }
    }
  }
  rep(it, 0, 300) {  // polygon-circle area vs circle approximated by a 4000-gon
    vector<Pd> poly = randConvex(rnd(3, 10), 10);
    if (sz(poly) < 3) continue;
    Pd c{rndd(-8, 8), rndd(-8, 8)};
    double r = rndd(0.5, 9);
    vector<Pd> circ;
    int N = 4000;
    rep(i, 0, N) circ.push_back(c + Pd{cos(2 * M_PI * i / N), sin(2 * M_PI * i / N)} * r);
    for (int i = 0; i < sz(poly) && sz(circ); ++i) circ = polyCut(circ, poly[i], poly[(i + 1) % sz(poly)]);
    double want = sz(circ) ? area2(circ) / 2 : 0, got = polyCircle(poly, c, r);
    CHECK(fabs(got - want) < 1e-3 * max(1.0, r * r));
    reverse(all(poly));
    CHECK(fabs(polyCircle(poly, c, r) + got) < 1e-9 * max(1.0, r * r));
  }
  {  // 3D: cube and tetrahedra
    using Q = P3<ll>;
    vector<Q> v;
    rep(m, 0, 8) v.push_back({m & 1, m >> 1 & 1, m >> 2 & 1});
    // faces of the unit cube as outward triangles
    vector<array<int, 4>> quads{{0, 2, 3, 1}, {4, 5, 7, 6}, {0, 1, 5, 4}, {2, 6, 7, 3}, {0, 4, 6, 2}, {1, 3, 7, 5}};
    vector<array<Q, 3>> f;
    for (auto [a, b, c, d] : quads) f.push_back({v[a], v[b], v[c]}), f.push_back({v[a], v[c], v[d]});
    CHECK(near(volume(f), 1));
    rep(it, 0, 1000) {
      Q a{rnd(-5, 5), rnd(-5, 5), rnd(-5, 5)}, b{rnd(-5, 5), rnd(-5, 5), rnd(-5, 5)},
          c{rnd(-5, 5), rnd(-5, 5), rnd(-5, 5)}, d{rnd(-5, 5), rnd(-5, 5), rnd(-5, 5)};
      ll det = (b - a).cross(c - a).dot(d - a);
      if (det < 0) swap(b, c), det = -det;
      vector<array<Q, 3>> t{{a, c, b}, {a, b, d}, {a, d, c}, {b, c, d}};
      CHECK(near(volume(t), det / 6.0));
      Q n = (b - a).cross(c - a);
      CHECK(n.dot(b - a) == 0 && n.dot(c - a) == 0);
    }
  }
  rep(it, 0, 500) {  // Manhattan MST vs all pairs
    int n = rnd(1, 30);
    vector<P<ll>> ps(n);
    for (auto& p : ps) p = {rnd(-10, 10), rnd(-10, 10)};
    auto mst = [&](vector<array<ll, 3>> es) {
      sort(all(es));
      DSU d(n);
      ll w = 0;
      for (auto [c, i, j] : es) if (d.join(i, j)) w += c;
      return w;
    };
    vector<array<ll, 3>> all;
    rep(i, 0, n) rep(j, 0, i) all.push_back({llabs(ps[i].x - ps[j].x) + llabs(ps[i].y - ps[j].y), i, j});
    auto es = manhattanEdges(ps);
    CHECK(sz(es) <= 4 * n);
    for (auto [w, i, j] : es) CHECK(w == llabs(ps[i].x - ps[j].x) + llabs(ps[i].y - ps[j].y));
    CHECK(mst(es) == mst(all));
  }
}
