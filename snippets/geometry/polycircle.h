/**
 * Name: Polygon and circle intersection
 * Description: Area of the intersection of a simple polygon
 *   (either orientation; the result is signed like the polygon's
 *   area) with the circle $(c, r)$. Sums, over the edges $a b$, the
 *   signed area of triangle $c a b$ inside the circle: the part of
 *   the edge inside the circle gives a triangle, the parts outside
 *   give circular sectors $r^2 theta \/ 2$.
 * Time: $O(n)$
 */
#pragma once
#include "point.h"
double polyCircle(const vector<Pd>& poly, Pd c, double r) {
  auto arg = [](Pd p, Pd q) {
    return atan2(p.cross(q), p.dot(q));
  };
  auto tri = [&](Pd p, Pd q) { // relative to c
    double r2 = r * r / 2;
    Pd d = q - p;
    if (d.dist2() == 0) return 0.0;
    double a = d.dot(p) / d.dist2();
    double b = (p.dist2() - r * r) / d.dist2();
    double e = sqrt(max(0.0, a * a - b));
    double s = max(0.0, -a - e), t = min(1.0, -a + e);
    if (s >= t) return arg(p, q) * r2; // misses the disc
    Pd u = p + d * s, v = p + d * t;
    return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
  };
  double sum = 0;
  rep(i, 0, sz(poly))
    sum += tri(poly[i] - c, poly[(i + 1) % sz(poly)] - c);
  return sum;
}
