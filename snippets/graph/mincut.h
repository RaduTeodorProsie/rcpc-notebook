/**
 * Name: Global min cut and Gomory–Hu
 * Description: Undirected graphs. `minCut(g)` (Stoer–Wagner,
 *   adjacency matrix of weights, $n >= 2$) is the cheapest way to
 *   split the vertices into two non-empty sides, with one side.
 *   Each phase adds vertices one at a time, always the one most
 *   strongly connected to those already added; the last vertex
 *   $t$ alone vs the rest is a minimum $s$-$t$ cut for the
 *   second-to-last $s$. Record it, merge $s$ and $t$ (no cut
 *   separates them any more), repeat. `gomoryHu(n, es)` returns
 *   $n - 1$ tree edges $(u, v, w)$ such that the min cut between
 *   any $a, b$ equals the smallest $w$ on the tree path $a..b$
 *   (all pairs from $n - 1$ flows). Gusfield: vertex $i$ hangs
 *   below `p[i]`; cut $i$ from `p[i]`, then the later vertices on
 *   $i$'s side with the same parent move below $i$.
 * Time: `minCut` $O(n^3)$, `gomoryHu` $n - 1$ calls of Dinic
 */
#pragma once
#include "dinic.h"
pair<ll, vi> minCut(vector<vector<ll>> g) {
  int n = sz(g);
  vector<vi> grp(n);
  rep(i, 0, n) grp[i] = {i};
  vector<bool> gone(n);
  pair<ll, vi> best{LLONG_MAX, {}};
  rep(ph, 1, n) {
    vector<ll> w(n);
    vector<bool> in(n);
    int s = -1, t = -1;
    ll cut = 0;
    rep(k, 0, n - ph + 1) {
      int v = -1;
      rep(i, 0, n) if (!gone[i] && !in[i] &&
                       (v < 0 || w[i] > w[v])) v = i;
      in[v] = 1, s = t, t = v, cut = w[v];
      rep(i, 0, n) w[i] += g[v][i];
    }
    if (cut < best.first) best = {cut, grp[t]};
    grp[s].insert(grp[s].end(), all(grp[t]));
    rep(i, 0, n) g[s][i] += g[t][i], g[i][s] = g[s][i];
    gone[t] = 1;
  }
  return best;
}
vector<array<ll, 3>> gomoryHu(int n,
                              vector<array<ll, 3>> es) {
  vi p(n);
  vector<array<ll, 3>> tree;
  rep(i, 1, n) {
    Dinic d(n);
    for (auto [a, b, c] : es) d.addEdge(a, b, c, c);
    tree.push_back({i, p[i], d.flow(i, p[i])});
    rep(j, i + 1, n)
      if (p[j] == p[i] && d.lvl[j] >= 0) p[j] = i;
  }
  return tree;
}
