/**
 * Name: Dinic max flow
 * Description: Max flow from $s$ to $t$. After `flow`, the
 *   min cut is the set of vertices with `lvl[v]` $>= 0$.
 * Time: $O(V^2 E)$, $O(E sqrt(V))$ for unit capacities
 * Usage: Dinic d(n); d.addEdge(a, b, c); d.flow(s, t);
 */
#pragma once
struct Dinic {
  struct E { int to, rev; ll c; };
  vector<vector<E>> g;
  vi lvl, it;
  Dinic(int n) : g(n), lvl(n), it(n) {}
  void addEdge(int a, int b, ll c, ll rc = 0) {
    g[a].push_back({b, sz(g[b]), c});
    g[b].push_back({a, sz(g[a]) - 1, rc});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    for (int& i = it[v]; i < sz(g[v]); ++i) {
      E& e = g[v][i];
      if (e.c > 0 && lvl[e.to] == lvl[v] + 1)
        if (ll d = dfs(e.to, t, min(f, e.c))) {
          e.c -= d, g[e.to][e.rev].c += d;
          return d;
        }
    }
    return 0;
  }
  ll flow(int s, int t) {
    for (ll res = 0;;) {
      fill(all(lvl), -1);
      lvl[s] = 0;
      queue<int> q({s});
      while (sz(q)) {
        int v = q.front(); q.pop();
        for (E& e : g[v])
          if (e.c > 0 && lvl[e.to] < 0)
            lvl[e.to] = lvl[v] + 1, q.push(e.to);
      }
      if (lvl[t] < 0) return res;
      fill(all(it), 0);
      while (ll f = dfs(s, t, LLONG_MAX)) res += f;
    }
  }
};
// --- uses ---
// After flow(s, t): min cut side of s.
vector<bool> minCut(Dinic& d) {
  vector<bool> r(sz(d.g));
  rep(v, 0, sz(d.g)) r[v] = d.lvl[v] >= 0;
  return r;
}
// Lower bounds: edges (a, b, lo, hi). Is there a flow
// from s to t (any value) with lo <= f <= hi on each edge?
bool feasible(int n, vector<array<ll, 4>> es, int s,
              int t) {
  Dinic d(n + 2);
  vector<ll> ex(n);
  for (auto [a, b, lo, hi] : es)
    d.addEdge(a, b, hi - lo), ex[b] += lo, ex[a] -= lo;
  d.addEdge(t, s, LLONG_MAX / 4);
  ll need = 0;
  rep(v, 0, n) {
    if (ex[v] > 0) d.addEdge(n, v, ex[v]), need += ex[v];
    else d.addEdge(v, n + 1, -ex[v]);
  }
  return d.flow(n, n + 1) == need;
}
