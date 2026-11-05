/**
 * Name: Bridges, cut vertices, BCCs
 * Description: Undirected multigraph as an edge list. Finds
 *   `bridge[e]`, articulation points `cut[v]`, and `bcc`: edge
 *   ids grouped into biconnected components (self-loops are
 *   skipped). Removing the bridges gives the 2-edge-connected
 *   components.
 * Time: $O(V + E)$
 */
#pragma once
struct Lowlink {
  int t = 0;
  vector<vector<pii>> g;
  vi tin, low, cut, bridge, st;
  vector<vi> bcc;
  Lowlink(int n, const vector<pii>& es) : g(n), tin(n, -1),
      low(n), cut(n), bridge(sz(es)) {
    rep(i, 0, sz(es)) {
      auto [a, b] = es[i];
      g[a].push_back({b, i}), g[b].push_back({a, i});
    }
    rep(v, 0, n) if (tin[v] < 0) dfs(v, -1);
  }
  void dfs(int v, int pe) {
    tin[v] = low[v] = t++;
    int kids = 0;
    for (auto [u, e] : g[v]) {
      if (e == pe) continue;
      if (tin[u] < 0) {
        st.push_back(e), dfs(u, e), ++kids;
        low[v] = min(low[v], low[u]);
        if (low[u] > tin[v]) bridge[e] = 1;
        if (low[u] >= tin[v]) {
          if (pe >= 0) cut[v] = 1;
          bcc.emplace_back();
          int x;
          do {
            x = st.back(), st.pop_back();
            bcc.back().push_back(x);
          } while (x != e);
        }
      } else if (tin[u] < tin[v]) {
        st.push_back(e), low[v] = min(low[v], tin[u]);
      }
    }
    if (pe < 0 && kids > 1) cut[v] = 1;
  }
};
