#include "geometry/polycut.h"
#include "geometry/polygon.h"
#include "geometry/halfplane.h"
#include "geometry/circles.h"
#include "testlib.h"
double area(const vector<Pd>& v) { return v.empty() ? 0 : area2(v) / 2; }
int main() {
  rep(it, 0, 3000) {
    const double B = 100;
    vector<Pd> box{{-B, -B}, {B, -B}, {B, B}, {-B, B}};
    vector<HP> hs;
    rep(i, 0, 4) hs.push_back(HP(box[i], box[(i + 1) % 4]));
    vector<Pd> poly = box;
    int m = rnd(1, 8);
    rep(i, 0, m) {
      Pd p{rndd(-10, 10), rndd(-10, 10)}, q{rndd(-10, 10), rndd(-10, 10)};
      if ((q - p).len() < 1e-3) continue;
      hs.push_back(HP(p, q));
      poly = polyCut(poly, p, q);
    }
    double want = poly.empty() ? 0 : area(poly);
    auto got = halfPlanes(hs);
    double ga = got.empty() ? 0 : area(got);
    CHECK(fabs(ga - want) < 1e-5 * max(1.0, want), "it=%d got %f want %f", it, ga, want);
  }
  rep(it, 0, 5000) {
    Pd a{rndd(-5, 5), rndd(-5, 5)}, b{rndd(-5, 5), rndd(-5, 5)}, l1{rndd(-5, 5), rndd(-5, 5)}, l2{rndd(-5, 5), rndd(-5, 5)};
    double r1 = rndd(0.1, 5), r2 = rndd(0.1, 5);
    for (Pd x : circleCircle(a, r1, b, r2))
      CHECK(fabs((x - a).len() - r1) < 1e-6 && fabs((x - b).len() - r2) < 1e-6);
    double d = (a - b).len();
    bool meet = d <= r1 + r2 && d >= fabs(r1 - r2);
    CHECK(!circleCircle(a, r1, b, r2).empty() == meet);
    for (Pd x : circleLine(a, r1, l1, l2))
      CHECK(fabs((x - a).len() - r1) < 1e-6 && fabs(l1.cross(l2, x)) < 1e-6 * 100);
    CHECK(!circleLine(a, r1, l1, l2).empty() == (fabs(l1.cross(l2, a)) / (l2 - l1).len() <= r1));
    Pd c = circum(a, b, l1);
    if (fabs(a.cross(b, l1)) > 1e-2)
      CHECK(fabs((c - a).len() - (c - b).len()) < 1e-6 && fabs((c - a).len() - (c - l1).len()) < 1e-6);
  }
  rep(it, 0, 500) {  // minimum enclosing circle vs brute force
    int n = rnd(1, 10);
    vector<Pd> v(n);
    for (auto& p : v) p = {(double)rnd(-20, 20), (double)rnd(-20, 20)};
    auto [c, r] = mec(v);
    for (auto p : v) CHECK((p - c).len() <= r + 1e-7);
    double best = n == 1 ? 0 : 1e18;
    auto tryC = [&](Pd cc) {
      double rr = 0;
      for (auto p : v) rr = max(rr, (p - cc).len());
      best = min(best, rr);
    };
    rep(i, 0, n) rep(j, i + 1, n) {
      tryC((v[i] + v[j]) * 0.5);
      rep(k, j + 1, n) if (fabs(v[i].cross(v[j], v[k])) > 1e-9) tryC(circum(v[i], v[j], v[k]));
    }
    CHECK(fabs(r - best) < 1e-6, "it=%d r=%f best=%f", it, r, best);
  }
}
