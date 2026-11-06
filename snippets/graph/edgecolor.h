/**
 * Name: Edge colouring
 * Description: Colours the edges of a simple undirected graph
 *   with max degree $D$ using colours $0..D$ (Vizing: $D + 1$ is
 *   always enough), no two edges at a vertex alike. Bipartite
 *   graphs need only $D$: use matchings or Kőnig instead.
 *   Misra–Gries: rotate a fan, then flip an alternating path.
 * Time: $O(n m)$
 */
#pragma once
vi edgeColor(int n, vector<pii> es) {
  vi cc(n + 1), ret(sz(es)), fan(n), fr(n), loc;
  for (auto [a, b] : es) ++cc[a], ++cc[b];
  int u, v, nc = *max_element(all(cc)) + 1;
  vector<vi> adj(n, vi(nc, -1)); // adj[x][c]: other end
  for (auto e : es) {
    tie(u, v) = e;
    fan[0] = v;
    loc.assign(nc, 0);
    int at = u, end = u, d, c = fr[u], ind = 0, i = 0;
    while (d = fr[v], !loc[d] && (v = adj[u][d]) != -1)
      loc[d] = ++ind, cc[ind] = d, fan[ind] = v;
    cc[loc[d]] = c;
    for (int cd = d; at != -1;
         cd ^= c ^ d, at = adj[at][cd])
      swap(adj[at][cd], adj[end = at][cd ^ c ^ d]);
    while (adj[fan[i]][d] != -1) {
      int l = fan[i], r = fan[++i], e = cc[i];
      adj[u][e] = l, adj[l][e] = u;
      adj[r][e] = -1, fr[r] = e;
    }
    adj[u][d] = fan[i], adj[fan[i]][d] = u;
    for (int y : {fan[0], u, end})
      for (int& z = fr[y] = 0; adj[y][z] != -1; z++);
  }
  rep(i, 0, sz(es))
    for (tie(u, v) = es[i]; adj[u][ret[i]] != v;) ++ret[i];
  return ret;
}
