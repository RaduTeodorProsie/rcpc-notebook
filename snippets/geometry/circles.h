/**
 * Name: Circles
 * Description: Intersections of a circle with a line or another
 *   circle (a tangent gives two equal points; none if concentric).
 *   `circum`: circumcentre. `mec`: minimum enclosing circle.
 * Time: `mec` $O(n)$ expected
 */
#pragma once
#include "point.h"
vector<Pd> circleLine(Pd c, double r, Pd a, Pd b) {
  Pd d = b - a, p = a + d * ((c - a).dot(d) / d.dist2());
  double h2 = r * r - (c - p).dist2();
  if (h2 < -1e-9) return {};
  Pd off = d * (sqrt(max(0.0, h2)) / d.len());
  return {p - off, p + off};
}
vector<Pd> circleCircle(Pd a, double r1, Pd b, double r2) {
  Pd d = b - a;
  double d2 = d.dist2();
  if (d2 == 0) return {};
  double x = (d2 + r1 * r1 - r2 * r2) / (2 * d2);
  double h2 = r1 * r1 - x * x * d2;
  if (h2 < -1e-9) return {};
  Pd m = a + d * x;
  Pd off = d.perp() * sqrt(max(0.0, h2) / d2);
  return {m - off, m + off};
}
Pd circum(Pd a, Pd b, Pd c) {
  Pd u = b - a, v = c - a;
  return a + (u * v.dist2() - v * u.dist2()).perp() *
                 (1 / (2 * u.cross(v)));
}
pair<Pd, double> mec(vector<Pd> v) {
  shuffle(all(v), mt19937(1));
  Pd c = v[0];
  double r = 0, e = 1 + 1e-9;
  rep(i, 0, sz(v)) if ((v[i] - c).len() > r * e) {
    c = v[i], r = 0;
    rep(j, 0, i) if ((v[j] - c).len() > r * e) {
      c = (v[i] + v[j]) * 0.5, r = (v[i] - c).len();
      rep(k, 0, j) if ((v[k] - c).len() > r * e)
        c = circum(v[i], v[j], v[k]), r = (v[i] - c).len();
    }
  }
  return {c, r};
}
