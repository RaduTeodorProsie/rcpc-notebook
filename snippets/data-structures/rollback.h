/**
 * Name: Union-find with rollback
 * Description: No path compression; `rollback(t)` undoes every
 *   join after `time()` returned $t$. Uses: offline dynamic
 *   connectivity. Edges live on time intervals $[l, r)$; `run`
 *   gives the number of components at each time.
 * Time: $O(log n)$ per operation; uses $O(q log q log n)$
 */
#pragma once
struct RollbackDSU {
  vi p;
  vector<pii> hist;
  int comps;
  RollbackDSU(int n) : p(n, -1), comps(n) {}
  int find(int x) { return p[x] < 0 ? x : find(p[x]); }
  int time() { return sz(hist); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (p[a] > p[b]) swap(a, b);
    hist.push_back({b, p[b]});
    p[a] += p[b], p[b] = a, --comps;
    return true;
  }
  void rollback(int t) {
    while (sz(hist) > t) {
      auto [b, pb] = hist.back();
      hist.pop_back();
      p[p[b]] -= pb, p[b] = pb, ++comps;
    }
  }
};
// --- uses ---
struct DynConn {
  int T;
  vector<vector<pii>> seg;
  DynConn(int T) : T(T), seg(4 * T) {}
  void add(int l, int r, pii e, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) return seg[x].push_back(e);
    int m = (lo + hi) / 2;
    add(l, r, e, 2 * x, lo, m);
    add(l, r, e, 2 * x + 1, m, hi);
  }
  void addEdge(int a, int b, int l, int r) {
    add(l, r, {a, b}, 1, 0, T);
  }
  void go(RollbackDSU& d, vi& res, int x, int lo, int hi) {
    int t = d.time();
    for (auto [a, b] : seg[x]) d.join(a, b);
    if (hi - lo == 1) res[lo] = d.comps;
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
    go(d, res, 1, 0, T);
    return res;
  }
};
