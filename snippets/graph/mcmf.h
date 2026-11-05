/**
 * Name: Min-cost max-flow
 * Description: Successive shortest paths with SPFA, so negative
 *   costs are fine (no negative cycles). Returns (flow, cost);
 *   `lim` caps the flow.
 * Time: $O(F V E)$ worst case, fast in practice
 */
#pragma once
struct MCMF {
  struct E { int to, rev; ll cap, cost; };
  int n;
  vector<vector<E>> g;
  MCMF(int n) : n(n), g(n) {}
  void addEdge(int a, int b, ll cap, ll cost) {
    g[a].push_back({b, sz(g[b]), cap, cost});
    g[b].push_back({a, sz(g[a]) - 1, 0, -cost});
  }
  pair<ll, ll> flow(int s, int t, ll lim = LLONG_MAX) {
    ll f = 0, c = 0;
    while (f < lim) {
      vector<ll> d(n, LLONG_MAX);
      vi inq(n), pv(n), pe(n);
      deque<int> q{s};
      d[s] = 0;
      while (sz(q)) {
        int v = q.front();
        q.pop_front(), inq[v] = 0;
        rep(i, 0, sz(g[v])) {
          E& e = g[v][i];
          if (e.cap > 0 && d[v] + e.cost < d[e.to]) {
            d[e.to] = d[v] + e.cost;
            pv[e.to] = v, pe[e.to] = i;
            if (!inq[e.to]++) q.push_back(e.to);
          }
        }
      }
      if (d[t] == LLONG_MAX) break;
      ll push = lim - f;
      for (int v = t; v != s; v = pv[v])
        push = min(push, g[pv[v]][pe[v]].cap);
      for (int v = t; v != s; v = pv[v]) {
        E& e = g[pv[v]][pe[v]];
        e.cap -= push, g[v][e.rev].cap += push;
      }
      f += push, c += push * d[t];
    }
    return {f, c};
  }
};
