/**
 * Name: Closest pair
 * Description: Smallest squared distance between two of the
 *   points ($n >= 2$), by a sweep over $x$.
 * Time: $O(n log n)$
 */
#pragma once
#include "point.h"
ll closestPair(vector<P<ll>> v) {
  sort(all(v));
  set<pair<ll, ll>> s; // (y, x) of points in the strip
  ll best = LLONG_MAX;
  int j = 0;
  for (auto p : v) {
    ll d = (ll)sqrtl((long double)best) + 1;
    for (; p.x - v[j].x >= d; ++j)
      s.erase({v[j].y, v[j].x});
    auto it = s.lower_bound({p.y - d, LLONG_MIN});
    for (; it != s.end() && it->first < p.y + d; ++it) {
      ll dx = p.x - it->second, dy = p.y - it->first;
      best = min(best, dx * dx + dy * dy);
    }
    s.insert({p.y, p.x});
  }
  return best;
}
