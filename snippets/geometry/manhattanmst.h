/**
 * Name: Manhattan MST
 * Description: Candidate edges $(w, i, j)$, at most $4 n$, that
 *   contain a minimum spanning tree for the distance
 *   $|x_i - x_j| + |y_i - y_j|$: each point only needs its nearest
 *   neighbour in each of the $8$ octants. Sort them and run
 *   Kruskal (`dsu.h`).
 * Time: $O(n log n)$
 */
#pragma once
#include "point.h"
vector<array<ll, 3>> manhattanEdges(vector<P<ll>> ps) {
  vi id(sz(ps));
  iota(all(id), 0);
  vector<array<ll, 3>> es;
  rep(k, 0, 4) {
    sort(all(id), [&](int i, int j) {
      return (ps[i] - ps[j]).x < (ps[j] - ps[i]).y;
    });
    map<ll, int> sweep;
    for (int i : id) {
      for (auto it = sweep.lower_bound(-ps[i].y);
           it != sweep.end(); sweep.erase(it++)) {
        int j = it->second;
        P<ll> d = ps[i] - ps[j];
        if (d.y > d.x) break;
        es.push_back({d.y + d.x, i, j});
      }
      sweep[-ps[i].y] = i;
    }
    for (auto& p : ps)
      if (k & 1) p.x = -p.x;
      else swap(p.x, p.y);
  }
  return es;
}
