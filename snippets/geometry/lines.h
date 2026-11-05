/**
 * Name: Segments and lines
 * Description: `segInter`: do closed segments $a b$ and $c d$ meet
 *   (exact for `ll`). `lineInter`: intersection of lines $a b$
 *   and $c d$ (not parallel). `segDist`: distance from $p$ to
 *   segment $a b$. `onSeg`: $p$ on closed segment $a b$.
 */
#pragma once
#include "point.h"
template <class T> bool onSeg(P<T> p, P<T> a, P<T> b) {
  return p.cross(a, b) == 0 && (a - p).dot(b - p) <= 0;
}
template <class T>
bool segInter(P<T> a, P<T> b, P<T> c, P<T> d) {
  int o1 = sgn(a.cross(b, c)), o2 = sgn(a.cross(b, d)),
      o3 = sgn(c.cross(d, a)), o4 = sgn(c.cross(d, b));
  if (o1 * o2 < 0 && o3 * o4 < 0) return true;
  return onSeg(c, a, b) || onSeg(d, a, b) ||
         onSeg(a, c, d) || onSeg(b, c, d);
}
Pd lineInter(Pd a, Pd b, Pd c, Pd d) {
  double t = (c - a).cross(d - c) / (b - a).cross(d - c);
  return a + (b - a) * t;
}
double segDist(Pd p, Pd a, Pd b) {
  Pd d = b - a;
  double t = d.dist2() ? (p - a).dot(d) / d.dist2() : 0;
  return (p - (a + d * clamp(t, 0.0, 1.0))).len();
}
