/**
 * Name: Maximum clique
 * Description: Branch and bound; a greedy colouring of the
 *   candidates bounds how much a branch can still add. `g[v]` is
 *   the neighbour set of $v$ (symmetric, no self-loops). Max
 *   independent set: the clique of the complement. Random
 *   graphs, $n = 128$: $< 50$ ms up to edge density $0.8$,
 *   about 2 s at $0.95$.
 * Usage: MaxClique mc(g); vi c = mc.run();
 * Time: exponential
 */
#pragma once
using B = bitset<128>; //!
struct MaxClique {
  vector<B> g;
  vi cur, best;
  MaxClique(vector<B> g) : g(g) {}
  void go(B P) {
    if (P.none()) {
      if (sz(cur) > sz(best)) best = cur;
      return;
    }
    vector<pii> ord; // (colour, v), colours increasing
    B U = P;
    for (int k = 1; U.any(); ++k)
      for (B Q = U; Q.any();) {
        int v = Q._Find_first();
        Q &= ~g[v], Q[v] = U[v] = 0;
        ord.push_back({k, v});
      }
    for (int i = sz(ord); i--;) {
      auto [k, v] = ord[i];
      if (sz(cur) + k <= sz(best)) return;
      cur.push_back(v);
      go(P & g[v]);
      cur.pop_back(), P[v] = 0;
    }
  }
  vi run() {
    B P;
    rep(i, 0, sz(g)) P[i] = 1;
    go(P);
    return best;
  }
};
