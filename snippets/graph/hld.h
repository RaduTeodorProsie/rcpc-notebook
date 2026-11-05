/**
 * Name: Heavy-light decomposition
 * Description: `pos[v]` orders vertices so that heavy paths and
 *   subtrees are contiguous; the subtree of $v$ is
 *   $[p o s_v, p o s_v + s i z_v)$. `path(a, b, f)` calls `f(l, r)`
 *   on $O(log n)$ ranges $[l, r)$ covering the path; with
 *   `edges`, the LCA is skipped (edge values live at the child).
 * Time: $O(log n)$ ranges per path
 */
#pragma once
struct HLD {
  int n, cnt = 0;
  vector<vi> g;
  vi par, dep, siz, heavy, head, pos;
  HLD(const vector<vi>& g, int root = 0) : n(sz(g)), g(g),
      par(n, -1), dep(n), siz(n, 1), heavy(n, -1), head(n),
      pos(n) {
    dfs(root), decomp(root, root);
  }
  void dfs(int v) {
    for (int u : g[v])
      if (u != par[v]) {
        par[u] = v, dep[u] = dep[v] + 1, dfs(u);
        siz[v] += siz[u];
        int& h = heavy[v];
        if (h < 0 || siz[u] > siz[h]) h = u;
      }
  }
  void decomp(int v, int h) {
    head[v] = h, pos[v] = cnt++;
    if (heavy[v] >= 0) decomp(heavy[v], h);
    for (int u : g[v])
      if (u != par[v] && u != heavy[v]) decomp(u, u);
  }
  template <class F>
  void path(int a, int b, F f, bool edges = false) {
    for (; head[a] != head[b]; b = par[head[b]]) {
      if (pos[head[a]] > pos[head[b]]) swap(a, b);
      f(pos[head[b]], pos[b] + 1);
    }
    if (pos[a] > pos[b]) swap(a, b);
    if (pos[a] + edges <= pos[b])
      f(pos[a] + edges, pos[b] + 1);
  }
  int lca(int a, int b) {
    for (; head[a] != head[b]; b = par[head[b]])
      if (pos[head[a]] > pos[head[b]]) swap(a, b);
    return pos[a] < pos[b] ? a : b;
  }
};
