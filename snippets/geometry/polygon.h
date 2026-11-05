/**
 * Name: Polygon area and containment
 * Description: `area2` is twice the signed area, positive for
 *   counter-clockwise order. `inside` returns $1$ strictly
 *   inside, $0$ on the boundary, $-1$ outside. Exact on `ll`.
 * Time: $O(n)$
 */
#pragma once
#include "point.h"
template <class T> T area2(const vector<P<T>>& v) {
  T a = 0;
  rep(i, 0, sz(v)) a += v[i].cross(v[(i + 1) % sz(v)]);
  return a;
}
template <class T>
int inside(const vector<P<T>>& v, P<T> q) {
  int n = sz(v), w = 0;
  rep(i, 0, n) {
    P<T> a = v[i], b = v[(i + 1) % n];
    if (q.cross(a, b) == 0 && (a - q).dot(b - q) <= 0)
      return 0;
    if ((a.y <= q.y) != (b.y <= q.y)) {
      T c = (b - a).cross(q - a);
      if ((c > 0) == (b.y > a.y)) w ^= 1;
    }
  }
  return w ? 1 : -1;
}
