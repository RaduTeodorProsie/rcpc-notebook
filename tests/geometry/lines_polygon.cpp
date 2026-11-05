#include "geometry/lines.h"
#include "geometry/polygon.h"
#include "testlib.h"
using Pl = P<ll>;
Pl rp(int c) { return {rnd(-c, c), rnd(-c, c)}; }
// Exact brute: segments as parametric, rational comparison.
bool bruteInter(Pl a, Pl b, Pl c, Pl d) {
  auto onBox = [](Pl p, Pl x, Pl y) {  // p on segment xy, by bounding box
    return (x - p).cross(y - p) == 0 && min(x.x, y.x) <= p.x && p.x <= max(x.x, y.x) &&
           min(x.y, y.y) <= p.y && p.y <= max(x.y, y.y);
  };
  if (a == b) return onBox(a, c, d);
  if (c == d) return onBox(c, a, b);
  Pl r = b - a, s = d - c;
  ll den = r.cross(s), tn = (c - a).cross(s), un = (c - a).cross(r);
  if (den == 0) {
    if ((c - a).cross(r) != 0) return false;  // parallel, not collinear
    // collinear: project on the dominant axis
    auto key = [&](Pl p) { return r.x != 0 || s.x != 0 ? p.x : p.y; };
    ll lo1 = min(key(a), key(b)), hi1 = max(key(a), key(b));
    ll lo2 = min(key(c), key(d)), hi2 = max(key(c), key(d));
    if (r == Pl{0, 0} && s == Pl{0, 0}) return a == c;
    return max(lo1, lo2) <= min(hi1, hi2);
  }
  if (den < 0) den = -den, tn = -tn, un = -un;
  return 0 <= tn && tn <= den && 0 <= un && un <= den;
}
int main() {
  rep(it, 0, 200000) {
    int c = rnd(1, 4);
    Pl a = rp(c), b = rp(c), cc = rp(c), d = rp(c);
    CHECK(segInter(a, b, cc, d) == bruteInter(a, b, cc, d),
          "(%lld,%lld)-(%lld,%lld) (%lld,%lld)-(%lld,%lld)", a.x, a.y, b.x, b.y, cc.x, cc.y, d.x, d.y);
  }
  rep(it, 0, 5000) {
    Pd a{rndd(-10, 10), rndd(-10, 10)}, b{rndd(-10, 10), rndd(-10, 10)},
       c{rndd(-10, 10), rndd(-10, 10)}, d{rndd(-10, 10), rndd(-10, 10)}, p{rndd(-10, 10), rndd(-10, 10)};
    if (fabs((b - a).cross(d - c)) > 1e-3) {
      Pd x = lineInter(a, b, c, d);
      CHECK(fabs(a.cross(b, x)) < 1e-6 * (b - a).len() * 100 && fabs(c.cross(d, x)) < 1e-6 * (d - c).len() * 100);
    }
    double best = 1e18;
    rep(i, 0, 2001) best = min(best, (p - (a + (b - a) * (i / 2000.0))).len());
    CHECK(fabs(segDist(p, a, b) - best) < 1e-2);
  }
  rep(it, 0, 3000) {  // star-shaped simple polygons
    int n = rnd(3, 12);
    vector<pair<double, Pl>> pts;
    set<pair<ll, ll>> used;
    while (sz(pts) < n) {
      Pl p = rp(20);
      if (p == Pl{0, 0} || used.count({p.x, p.y})) continue;
      used.insert({p.x, p.y});
      pts.push_back({atan2((double)p.y, (double)p.x), p});
    }
    sort(all(pts), [](auto& x, auto& y) { return x.first < y.first || (x.first == y.first && x.second.dist2() < y.second.dist2()); });
    vector<Pl> poly;
    for (auto& [ang, p] : pts) poly.push_back(p);
    bool simple = true;
    rep(i, 0, n) rep(j, i + 1, n) {
      int i2 = (i + 1) % n, j2 = (j + 1) % n;
      bool adj = i2 == j || j2 == i;
      if (!adj && segInter(poly[i], poly[i2], poly[j], poly[j2])) simple = false;
    }
    rep(i, 0, n) if (poly[i].cross(poly[(i + 1) % n], poly[(i + 2) % n]) == 0 &&
                     (poly[(i + 1) % n] - poly[i]).dot(poly[(i + 2) % n] - poly[(i + 1) % n]) < 0) simple = false;
    if (!simple) continue;
    ll A = 0;
    rep(i, 0, n) A += poly[i].cross(poly[(i + 1) % n]);
    CHECK(area2(poly) == A);
    rep(q, 0, 30) {
      Pl p = rp(22);
      bool on = false;
      rep(i, 0, n) on |= onSeg(p, poly[i], poly[(i + 1) % n]);
      double w = 0;
      if (!on) rep(i, 0, n) {
        Pd a{(double)(poly[i].x - p.x), (double)(poly[i].y - p.y)};
        Pd b{(double)(poly[(i + 1) % n].x - p.x), (double)(poly[(i + 1) % n].y - p.y)};
        w += atan2(a.cross(b), a.dot(b));
      }
      int want = on ? 0 : (fabs(w) > 3 ? 1 : -1);
      CHECK(inside(poly, p) == want);
    }
  }
}
