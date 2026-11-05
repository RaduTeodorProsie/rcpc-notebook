/**
 * Name: Hopcroft-Karp
 * Description: Maximum bipartite matching; `ml[a]` / `mr[b]` is
 *   the partner or $-1$. The minimum vertex cover's complement
 *   is a maximum independent set.
 * Time: $O(E sqrt(V))$
 */
#pragma once
struct HK {
  int n, m;
  vector<vi> g;
  vi ml, mr, dist;
  HK(int n, int m)
      : n(n), m(m), g(n), ml(n, -1), mr(m, -1) {}
  void addEdge(int a, int b) { g[a].push_back(b); }
  bool bfs() {
    dist.assign(n, -1);
    queue<int> q;
    rep(a, 0, n) if (ml[a] < 0) dist[a] = 0, q.push(a);
    bool found = false;
    while (sz(q)) {
      int a = q.front();
      q.pop();
      for (int b : g[a]) {
        int c = mr[b];
        if (c < 0) found = true;
        else if (dist[c] < 0)
          dist[c] = dist[a] + 1, q.push(c);
      }
    }
    return found;
  }
  bool dfs(int a) {
    for (int b : g[a]) {
      int c = mr[b];
      if (c < 0 || (dist[c] == dist[a] + 1 && dfs(c)))
        return ml[a] = b, mr[b] = a, true;
    }
    dist[a] = -1;
    return false;
  }
  int run() {
    int res = 0;
    while (bfs())
      rep(a, 0, n) if (ml[a] < 0 && dfs(a)) ++res;
    return res;
  }
};
// --- uses ---
// After run(): (left, right) parts of a min vertex cover.
pair<vi, vi> vertexCover(HK& h) {
  vector<bool> vl(h.n), vr(h.m);
  queue<int> q;
  rep(a, 0, h.n) if (h.ml[a] < 0) vl[a] = 1, q.push(a);
  while (sz(q)) {
    int a = q.front();
    q.pop();
    for (int b : h.g[a])
      if (!vr[b]) {
        vr[b] = 1;
        int c = h.mr[b];
        if (c >= 0 && !vl[c]) vl[c] = 1, q.push(c);
      }
  }
  vi L, R;
  rep(a, 0, h.n) if (!vl[a]) L.push_back(a);
  rep(b, 0, h.m) if (vr[b]) R.push_back(b);
  return {L, R};
}
