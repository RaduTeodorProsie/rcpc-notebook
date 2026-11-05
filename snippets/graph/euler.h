/**
 * Name: Euler path
 * Description: Eulerian path or cycle from `src` using every edge
 *   once. Returns the vertex sequence, or empty if there is none
 *   (bad degrees or disconnected). Works on multigraphs.
 * Time: $O(V + E)$
 */
#pragma once
vi eulerPath(int n, const vector<pii>& es, bool directed,
             int src = 0) {
  vector<vector<pii>> g(n);
  vi deg(n), used(sz(es)), it(n), path, st{src};
  rep(i, 0, sz(es)) {
    auto [a, b] = es[i];
    g[a].push_back({b, i});
    if (directed) ++deg[a], --deg[b];
    else g[b].push_back({a, i}), ++deg[a], ++deg[b];
  }
  int odd = 0;
  rep(v, 0, n) {
    int want = v == src ? 1 : -1;
    if (directed && deg[v] && deg[v] != want) return {};
    odd += !directed && deg[v] % 2;
  }
  if (odd && (odd != 2 || deg[src] % 2 == 0)) return {};
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
