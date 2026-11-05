/**
 * Name: Minkowski sum
 * Description: Sum of two convex polygons, each counter-clockwise
 *   with at least 2 points; the result is convex and
 *   counter-clockwise but may contain collinear points. Distance
 *   between convex $A$ and $B$: distance from origin to $A + (-B)$.
 * Time: $O(n + m)$
 */
#pragma once
#include "point.h"
template <class T>
vector<P<T>> minkowski(vector<P<T>> a, vector<P<T>> b) {
  auto fix = [](vector<P<T>>& v) {
    int k = 0;
    rep(i, 1, sz(v)) if (tie(v[i].y, v[i].x) <
                         tie(v[k].y, v[k].x)) k = i;
    rotate(v.begin(), v.begin() + k, v.end());
    v.push_back(v[0]), v.push_back(v[1]);
  };
  fix(a), fix(b);
  vector<P<T>> r;
  int i = 0, j = 0, n = sz(a) - 2, m = sz(b) - 2;
  while (i < n || j < m) {
    r.push_back(a[i] + b[j]);
    T c = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
    if (c >= 0 && i < n) ++i;
    if (c <= 0 && j < m) ++j;
  }
  return r;
}
