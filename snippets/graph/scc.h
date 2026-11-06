/**
 * Name: Strongly connected components
 * Description: Tarjan. `comp[v]` is the component of $v$,
 *   numbered bottom-up (reverse topological order): component $0$
 *   is a sink, and an edge $u -> v$ between components always has
 *   `comp[u] > comp[v]`. So a DP over the condensation that needs
 *   the successors first just runs $0, 1, 2, dots$
 * Time: $O(V + E)$
 */
#pragma once
struct SCC {
  vector<vi> g;
  vi low, num, comp, st;
  int t = 0, ncomp = 0;
  SCC(const vector<vi>& g) : g(g), low(sz(g)),
      num(sz(g), -1), comp(sz(g), -1) {
    rep(v, 0, sz(g)) if (num[v] < 0) dfs(v);
  }
  void dfs(int v) {
    low[v] = num[v] = t++;
    st.push_back(v);
    for (int u : g[v]) {
      if (num[u] < 0) dfs(u), low[v] = min(low[v], low[u]);
      else if (comp[u] < 0) low[v] = min(low[v], num[u]);
    }
    if (low[v] == num[v]) {
      int u;
      do u = st.back(), st.pop_back(), comp[u] = ncomp;
      while (u != v);
      ++ncomp;
    }
  }
};
