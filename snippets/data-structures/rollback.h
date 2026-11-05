/**
 * Name: Union-find with rollback
 * Description: No path compression, so `rollback(t)` can undo
 *   every join made after `time()` returned $t$. Keeps the number
 *   of components in `comps`.
 * Time: $O(log n)$ per operation
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
