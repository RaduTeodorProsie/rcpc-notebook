/**
 * Name: Half-plane intersection
 * Description: Each half-plane is the left side of the directed
 *   line from `p` to `q`. Returns the vertices of the bounded
 *   intersection in counter-clockwise order, or empty. Add four
 *   big box sides if the result could be unbounded.
 * Time: $O(n log n)$
 */
#pragma once
#include "point.h"
struct HP {
  Pd p, d;
  double ang;
  HP(Pd a, Pd b) : p(a), d(b - a), ang(atan2(d.y, d.x)) {}
  bool out(Pd r) const { return d.cross(r - p) < -1e-9; }
};
Pd inter(const HP& s, const HP& t) {
  double k = (t.p - s.p).cross(t.d) / s.d.cross(t.d);
  return s.p + s.d * k;
}
vector<Pd> halfPlanes(vector<HP> H) {
  sort(all(H), [](auto& a, auto& b) {
    return a.ang < b.ang;
  });
  deque<HP> dq;
  auto last2 = [&] {
    return inter(dq.back(), dq.end()[-2]);
  };
  for (auto& h : H) {
    while (sz(dq) > 1 && h.out(last2()))
      dq.pop_back();
    while (sz(dq) > 1 && h.out(inter(dq[0], dq[1])))
      dq.pop_front();
    if (sz(dq) && fabs(h.d.cross(dq.back().d)) < 1e-12) {
      if (h.d.dot(dq.back().d) < 0) return {};
      if (!h.out(dq.back().p)) continue;
      dq.pop_back();
    }
    dq.push_back(h);
  }
  while (sz(dq) > 2 && dq[0].out(last2()))
    dq.pop_back();
  while (sz(dq) > 2 && dq.back().out(inter(dq[0], dq[1])))
    dq.pop_front();
  if (sz(dq) < 3) return {};
  vector<Pd> res;
  rep(i, 0, sz(dq))
    res.push_back(inter(dq[i], dq[(i + 1) % sz(dq)]));
  return res;
}
