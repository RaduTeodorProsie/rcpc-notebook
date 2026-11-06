/**
 * Name: Dominator tree
 * Description: Directed graph, source $s$. $u$ dominates $v$ if
 *   every path from $s$ to $v$ passes through $u$. The dominators
 *   of $v$ form a chain $s, dots, v$; the last one before $v$ is
 *   `idom[v]`, and these are the parents of the dominator tree
 *   (`idom[s]` $= s$, $-1$ if not reachable from $s$). Use:
 *   vertices whose removal cuts $s$ from $t$ are the ancestors of
 *   $t$ in this tree; for edges, put a vertex in the middle of
 *   each. Lengauer–Tarjan: number the vertices in DFS order. The
 *   semidominator `sdom[v]` is the smallest number from which a
 *   path reaches $v$ through vertices numbered above $v$ only; it
 *   is computed backwards in DFS order with a DSU that returns the
 *   smallest `sdom` on a forest path. Then
 *   $"idom"(v) = "sdom"(v)$ unless some $u$ on the tree path
 *   $"sdom"(v) .. v$ has a smaller `sdom`, in which case
 *   $"idom"(v) = "idom"(u)$. Recursive DFS: mind the stack on
 *   long paths.
 * Time: $O((n + m) log n)$
 */
#pragma once
vi dominators(const vector<vi>& g, int s) {
  int n = sz(g), t = 0;
  vi num(n, -1), ord(n), par(n), sdom(n), dsu(n), best(n),
      id(n), idom(n, -1);
  vector<vi> rg(n), bk(n);
  auto dfs = [&](auto& dfs, int v) -> void {
    ord[t] = v, num[v] = t++;
    for (int u : g[v]) {
      if (num[u] < 0) dfs(dfs, u), par[num[u]] = num[v];
      rg[num[u]].push_back(num[v]);
    }
  };
  dfs(dfs, s);
  rep(i, 0, t) sdom[i] = dsu[i] = best[i] = i;
  auto find = [&](auto& find, int v, int d) -> int {
    if (dsu[v] == v) return d ? -1 : v;
    int r = find(find, dsu[v], d + 1);
    if (r < 0) return v;
    if (sdom[best[dsu[v]]] < sdom[best[v]])
      best[v] = best[dsu[v]];
    dsu[v] = r;
    return d ? r : best[v];
  };
  for (int i = t - 1; i >= 0; --i) {
    for (int j : rg[i])
      sdom[i] = min(sdom[i], sdom[find(find, j, 0)]);
    if (i) bk[sdom[i]].push_back(i);
    for (int w : bk[i]) {
      int u = find(find, w, 0);
      id[w] = sdom[u] == sdom[w] ? sdom[w] : u;
    }
    if (i) dsu[i] = par[i];
  }
  rep(i, 1, t) if (id[i] != sdom[i]) id[i] = id[id[i]];
  rep(i, 0, t) idom[ord[i]] = ord[i ? id[i] : 0];
  return idom;
}
