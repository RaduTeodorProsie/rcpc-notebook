/**
 * Name: Convex hull
 * Description: Monotone chain; hull in counter-clockwise order
 *   without collinear points. `inConvex`: is $p$ inside or on
 *   the boundary of such a hull with at least 3 points.
 *   `diameter2`: largest squared distance (rotating calipers).
 * Time: $O(n log n)$; $O(log n)$; $O(n)$
 */
#pragma once
#include "point.h"
template <class T> vector<P<T>> hull(vector<P<T>> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P<T>> h(2 * sz(pts));
  int k = 0;
  rep(it, 0, 2) {
    int start = k;
    for (auto& p : pts) {
      while (k >= start + 2 &&
             h[k - 2].cross(h[k - 1], p) <= 0)
        --k;
      h[k++] = p;
    }
    --k;
    reverse(all(pts));
  }
  h.resize(k - (k == 2 && h[0] == h[1]));
  return h;
}
template <class T>
bool inConvex(const vector<P<T>>& h, P<T> p) {
  int n = sz(h);
  if (h[0].cross(h[1], p) < 0) return false;
  if (h[0].cross(h[n - 1], p) > 0) return false;
  int lo = 1, hi = n - 1;
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    (h[0].cross(h[m], p) >= 0 ? lo : hi) = m;
  }
  return h[lo].cross(h[lo + 1], p) >= 0;
}
template <class T> T diameter2(const vector<P<T>>& h) {
  int n = sz(h);
  T best = 0;
  for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
    for (;; j = (j + 1) % n) {
      best = max(best, (h[i] - h[j]).dist2());
      P<T> e = h[(i + 1) % n] - h[i];
      if (e.cross(h[(j + 1) % n] - h[j]) <= 0) break;
    }
  return best;
}
