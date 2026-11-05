/**
 * Name: Polygon cut
 * Description: The part of a polygon on the left of the directed
 *   line $p -> q$ (points on the line are kept). A convex polygon
 *   gives a convex polygon, possibly empty or degenerate. A
 *   non-convex one may give several pieces joined along the line,
 *   but the area is still right.
 * Time: $O(n)$
 */
#pragma once
#include "point.h"
vector<Pd> polyCut(const vector<Pd>& poly, Pd p, Pd q) {
  vector<Pd> r;
  rep(i, 0, sz(poly)) {
    Pd a = poly[i], b = poly[(i + 1) % sz(poly)];
    double sa = p.cross(q, a), sb = p.cross(q, b);
    if (sa >= 0) r.push_back(a);
    if (sa * sb < 0)
      r.push_back(a + (b - a) * (sa / (sa - sb)));
  }
  return r;
}
