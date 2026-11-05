/**
 * Name: Offline dynamic connectivity
 * Description: Edges appear and disappear; get an answer at each
 *   time $t in [0, T)$. An edge alive during $[l, r)$ is stored in
 *   the $O(log T)$ segment tree nodes covering $[l, r)$. A DFS over
 *   the tree joins a node's edges on the way down and rolls them
 *   back on the way up, so each leaf $t$ sees exactly the graph at
 *   time $t$. To adapt: keep the needed data in `RollbackDSU`
 *   (sizes, sums, a parity bit for bipartiteness) and restore it
 *   in `rollback`; compute the answer on the marked line, e.g.
 *   `d.find(a) == d.find(b)` for a query stored at time $t$.
 *   `fromEvents` builds the intervals from a list of events.
 * Time: $O(T log T log n)$
 */
#pragma once
#include "rollback.h"
struct DynConn {
  int T;
  vector<vector<pii>> seg;
  DynConn(int T) : T(T), seg(4 * max(T, 1)) {}
  void add(int l, int r, pii e, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) return seg[x].push_back(e);
    int m = (lo + hi) / 2;
    add(l, r, e, 2 * x, lo, m);
    add(l, r, e, 2 * x + 1, m, hi);
  }
  // edge ab alive during [l, r)
  void addEdge(int a, int b, int l, int r) {
    if (l < r) add(l, r, {a, b}, 1, 0, T);
  }
  void go(RollbackDSU& d, vi& res, int x, int lo, int hi) {
    int t = d.time();
    for (auto [a, b] : seg[x]) d.join(a, b);
    if (hi - lo == 1) res[lo] = d.comps; //!
    else {
      int m = (lo + hi) / 2;
      go(d, res, 2 * x, lo, m);
      go(d, res, 2 * x + 1, m, hi);
    }
    d.rollback(t);
  }
  vi run(int n) {
    RollbackDSU d(n);
    vi res(T);
    if (T) go(d, res, 1, 0, T);
    return res;
  }
};
// --- uses ---
// ev[t] = {type, a, b}: 1 adds edge ab, -1 removes a copy
// of it, 0 does nothing. Time t sees the graph after ev[t].
DynConn fromEvents(int T, const vector<array<int, 3>>& ev) {
  DynConn dc(T);
  map<pii, vi> open; // start times of the live copies
  rep(t, 0, sz(ev)) {
    auto [ty, a, b] = ev[t];
    pii e = minmax(a, b);
    if (ty > 0) open[e].push_back(t);
    if (ty < 0 && sz(open[e])) { // absent edges are ignored
      dc.addEdge(a, b, open[e].back(), t);
      open[e].pop_back();
    }
  }
  for (auto& [e, v] : open)
    for (int l : v) dc.addEdge(e.first, e.second, l, T);
  return dc;
}
