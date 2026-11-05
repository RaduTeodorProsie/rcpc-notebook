/**
 * Name: Lowest common ancestor
 * Description: Binary lifting on a rooted tree given as an
 *   adjacency list. `tin`/`tout` are DFS entry/exit times: $a$ is
 *   an ancestor of $b$ iff `anc(a, b)`. Recursive DFS: mind the
 *   stack depth on paths.
 * Time: $O(n log n)$ build, $O(log n)$ query
 */
#pragma once
struct LCA {
  int L, timer = 0;
  vector<vi> up;
  vi dep, tin, tout;
  LCA(const vector<vi>& g, int root = 0)
      : L(__lg(sz(g)) + 1), up(L, vi(sz(g))), dep(sz(g)),
        tin(sz(g)), tout(sz(g)) {
    dfs(g, root, root);
    rep(k, 1, L) rep(v, 0, sz(g))
      up[k][v] = up[k - 1][up[k - 1][v]];
  }
  void dfs(const vector<vi>& g, int v, int p) {
    up[0][v] = p, tin[v] = timer++;
    for (int u : g[v])
      if (u != p) dep[u] = dep[v] + 1, dfs(g, u, v);
    tout[v] = timer;
  }
  bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
  }
  int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int k = L - 1; k >= 0; --k)
      if (dep[a] - (1 << k) >= dep[b]) a = up[k][a];
    if (a == b) return a;
    for (int k = L - 1; k >= 0; --k)
      if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
    return up[0][a];
  }
  int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
  }
};
