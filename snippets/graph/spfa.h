/**
 * Name: SPFA and negative cycles
 * Description: Shortest distances from $s$ with any edge weights
 *   (`g[v]` holds `{u, w}`; `LLONG_MAX` = unreachable). Returns
 *   (`d`, `neg`): `neg` iff a negative cycle is reachable from $s$
 *   (a path of $n$ edges repeats a vertex); then `d` is meaningless
 *   (for the $-infinity$ vertices use Bellman–Ford). Negative
 *   cycles anywhere, or difference
 *   constraints $x_v - x_u <= w$ (edge $u -> v$): add a vertex with
 *   $0$-edges to all others and start there. Weights all $>= 0$:
 *   use Dijkstra, SPFA can be forced to be slow.
 * Usage: auto [d, neg] = spfa(g, s);
 * Time: $O(n m)$ worst case, usually much faster
 */
#pragma once
pair<vector<ll>, bool> spfa(const vector<vector<pii>>& g,
                            int s) {
  int n = sz(g);
  vector<ll> d(n, LLONG_MAX);
  vi cnt(n), inq(n);
  queue<int> q;
  d[s] = 0, q.push(s), inq[s] = 1;
  while (sz(q)) {
    int v = q.front();
    q.pop(), inq[v] = 0;
    for (auto [u, w] : g[v])
      if (d[v] + w < d[u]) {
        d[u] = d[v] + w, cnt[u] = cnt[v] + 1;
        if (cnt[u] >= n) return {d, true};
        if (!inq[u]) inq[u] = 1, q.push(u);
      }
  }
  return {d, false};
}
