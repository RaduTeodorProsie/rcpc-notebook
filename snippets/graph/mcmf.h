/**
 * Name: Min-cost max-flow
 * Description: Successive shortest paths. Bellman–Ford once sets
 *   potentials `h`, so negative costs are fine (no negative
 *   cycles); then Dijkstra on the reduced costs
 *   $c + h_u - h_v >= 0$. Returns (flow, cost); `lim` caps the flow.
 * Usage: MCMF f(n); f.addEdge(a, b, cap, cost);
 *   auto [fl, co] = f.flow(s, t);
 * Time: $O(F E log V)$, plus $O(V E)$ once
 */
#pragma once
struct MCMF {
  static constexpr ll INF = LLONG_MAX / 4;
  struct E { int to, rev; ll cap, cost; };
  int n;
  vector<vector<E>> g;
  MCMF(int n) : n(n), g(n) {}
  void addEdge(int a, int b, ll cap, ll cost) {
    g[a].push_back({b, sz(g[b]), cap, cost});
    g[b].push_back({a, sz(g[a]) - 1, 0, -cost});
  }
  pair<ll, ll> flow(int s, int t, ll lim = LLONG_MAX) {
    vector<ll> h(n); // potentials, from a virtual source
    rep(it, 0, n) {
      bool ch = false;
      rep(v, 0, n) for (E& e : g[v])
        if (e.cap > 0 && h[v] + e.cost < h[e.to])
          h[e.to] = h[v] + e.cost, ch = true;
      if (!ch) break;
    }
    ll f = 0, c = 0;
    while (f < lim) {
      vector<ll> d(n, INF);
      vi pv(n), pe(n);
      priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                     greater<>> pq;
      pq.push({d[s] = 0, s});
      while (sz(pq)) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (dv > d[v]) continue;
        rep(i, 0, sz(g[v])) {
          E& e = g[v][i];
          ll nd = dv + e.cost + h[v] - h[e.to];
          if (e.cap > 0 && nd < d[e.to])
            d[e.to] = nd, pv[e.to] = v, pe[e.to] = i,
            pq.push({nd, e.to});
        }
      }
      if (d[t] == INF) break;
      rep(v, 0, n) if (d[v] < INF) h[v] += d[v];
      ll push = lim - f;
      for (int v = t; v != s; v = pv[v])
        push = min(push, g[pv[v]][pe[v]].cap);
      for (int v = t; v != s; v = pv[v]) {
        E& e = g[pv[v]][pe[v]];
        e.cap -= push, g[v][e.rev].cap += push;
      }
      f += push, c += push * (h[t] - h[s]);
    }
    return {f, c};
  }
};
