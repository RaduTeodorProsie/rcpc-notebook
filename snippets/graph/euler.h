/**
 * Name: Euler path
 * Description: Path or cycle using every edge once (multigraphs
 *   and loops are fine), as a vertex sequence; empty if there is
 *   none (bad degrees or edges not connected). Directed: needs
 *   out $=$ in everywhere (a cycle), or out $-$ in $= 1$ at the
 *   start and $-1$ at the end. Undirected: $0$ or $2$ odd
 *   vertices. `src = -1` picks the start: the out $-$ in $= 1$ or
 *   an odd vertex if any, else an end of edge 0; a given `src`
 *   must be such a vertex. Only one kind needed: replace `dir`
 *   by `true` or `false` and delete the dead branches.
 * Usage: eulerPath(n, es, true) // directed
 * Time: $O(V + E)$
 */
#pragma once
vi eulerPath(int n, const vector<pii>& es, bool dir,
             int src = -1) {
  vector<vector<pii>> g(n);
  vi deg(n), used(sz(es)), it(n), path;
  rep(i, 0, sz(es)) {
    auto [a, b] = es[i];
    g[a].push_back({b, i}), ++deg[a];
    if (dir) --deg[b]; // deg = out - in
    else g[b].push_back({a, i}), ++deg[b];
  }
  int s = -1, k = 0; // k: starts forced by degrees
  rep(v, 0, n) {
    if (dir ? deg[v] > 0 : deg[v] % 2) ++k, s = v;
    if (dir && deg[v] > 1) return {};
  }
  if (k > 2 - dir) return {};
  if (src < 0) src = k ? s : sz(es) ? es[0].first : 0;
  else if (k && (dir ? src != s : deg[src] % 2 == 0))
    return {};
  vi st{src};
  while (sz(st)) {
    int v = st.back();
    while (it[v] < sz(g[v]) && used[g[v][it[v]].second])
      ++it[v];
    if (it[v] == sz(g[v])) {
      path.push_back(v), st.pop_back();
      continue;
    }
    auto [u, e] = g[v][it[v]];
    used[e] = 1, st.push_back(u);
  }
  if (sz(path) != sz(es) + 1) return {};
  reverse(all(path));
  return path;
}
