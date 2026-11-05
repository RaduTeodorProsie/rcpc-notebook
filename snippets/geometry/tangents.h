/**
 * Name: Tangents
 * Description: Common tangents of two circles as (point on
 *   circle 1, point on circle 2): outer ones as given, inner ones
 *   with $-r_2$ instead of $r_2$. $0$, $1$ or $2$ lines; none for equal
 *   centres. From a point $p$: `tangents(c, r, p, 0)`, the touching
 *   points are the `.first`s (none if $p$ is inside, one if on).
 */
#pragma once
#include "point.h"
vector<pair<Pd, Pd>> tangents(Pd c1, double r1, Pd c2,
                              double r2) {
  Pd d = c2 - c1;
  double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
  if (d2 == 0 || h2 < 0) return {};
  vector<pair<Pd, Pd>> res;
  for (double s : {-1, 1}) {
    Pd v = (d * dr + d.perp() * (sqrt(h2) * s)) * (1 / d2);
    res.push_back({c1 + v * r1, c2 + v * r2});
  }
  if (h2 == 0) res.pop_back();
  return res;
}
