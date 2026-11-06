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
 *   $"idom"(v) = "idom"(u)$. No recursion, so long paths are fine.
 * Time: $O((n + m) log n)$
 */
#pragma once
vi dominators(const vector<vi>& g, int s) {
  int n = sz(g), t = 0;
  vi num(n, -1), ord(n), par(n), sdom(n), dsu(n), best(n),
      id(n), idom(n, -1);
  vector<vi> rg(n), bk(n);
  vi st{s}, it(n); // iterative DFS: no deep recursion
  ord[t] = s, num[s] = t++;
  while (sz(st)) {
    int v = st.back();
    if (it[v] == sz(g[v])) { st.pop_back(); continue; }
    int u = g[v][it[v]++];
    if (num[u] < 0)
      par[t] = num[v], ord[t] = u, num[u] = t++, st.push_back(u);
    rg[num[u]].push_back(num[v]);
  }
  rep(i, 0, t) sdom[i] = dsu[i] = best[i] = i;
  auto find = [&](int v) { // min sdom on the DSU path, compress
    if (dsu[v] == v) return v;
    st.clear(); // v and its ancestors below the top two
    for (int u = v; dsu[dsu[u]] != dsu[u]; u = dsu[u])
      st.push_back(u);
    int r = sz(st) ? dsu[st.back()] : dsu[v];
    for (int k = sz(st) - 1; k >= 0; --k) {
      int u = st[k], p = k + 1 < sz(st) ? st[k + 1] : r;
      if (sdom[best[p]] < sdom[best[u]]) best[u] = best[p];
      dsu[u] = r;
    }
    return best[v];
  };
  for (int i = t - 1; i >= 0; --i) {
    for (int j : rg[i])
      sdom[i] = min(sdom[i], sdom[find(j)]);
    if (i) bk[sdom[i]].push_back(i);
    for (int w : bk[i]) {
      int u = find(w);
      id[w] = sdom[u] == sdom[w] ? sdom[w] : u;
    }
    if (i) dsu[i] = par[i];
  }
  rep(i, 1, t) if (id[i] != sdom[i]) id[i] = id[id[i]];
  rep(i, 0, t) idom[ord[i]] = ord[i ? id[i] : 0];
  return idom;
}
