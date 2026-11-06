/**
 * Name: Directed MST
 * Description: Minimum arborescence: the cheapest set of edges in
 *   which every vertex except the root $r$ has exactly one
 *   incoming edge and all of them are reachable from $r$. Returns
 *   (cost, `par`) with `par[r]` $= -1$, or $(-1, {})$ if some vertex
 *   is unreachable. Chu–Liu/Edmonds: every vertex takes its
 *   cheapest incoming edge. If that makes a cycle, contract the
 *   cycle into one vertex; an edge entering the cycle at $v$ then
 *   costs $w - w_"in"(v)$, since taking it means dropping $v$'s
 *   cycle edge. Repeat. Each vertex keeps its incoming edges in a
 *   skew heap with a lazy add (merged on contraction), and the
 *   contractions are a rollback DSU, so the chosen edges can be
 *   read back by undoing them in reverse.
 * Time: $O(m log m)$
 */
#pragma once
#include "data-structures/rollback.h"
struct Arc { int a, b; ll w; };
pair<ll, vi> dmst(int n, int r, const vector<Arc>& es) {
  int m = sz(es);
  vector<Arc> key(es);
  vi L(m, -1), R(m, -1), heap(n, -1);
  vector<ll> lz(m);
  auto push = [&](int x) {
    key[x].w += lz[x];
    for (int c : {L[x], R[x]}) if (c >= 0) lz[c] += lz[x];
    lz[x] = 0;
  };
  auto merge = [&](auto& merge, int x, int y) -> int {
    if (x < 0 || y < 0) return max(x, y);
    push(x), push(y);
    if (key[x].w > key[y].w) swap(x, y);
    R[x] = merge(merge, y, R[x]), swap(L[x], R[x]);
    return x;
  };
  rep(i, 0, m) {
    int& h = heap[es[i].b];
    h = merge(merge, h, i);
  }
  RollbackDSU uf(n);
  ll res = 0;
  vi seen(n, -1), path(n), par(n);
  vector<Arc> Q(n), in(n, {-1, -1, 0});
  deque<tuple<int, int, vector<Arc>>> cycs;
  seen[r] = r;
  rep(s, 0, n) {
    int u = s, qi = 0, w;
    while (seen[u] < 0) {
      int x = heap[u];
      if (x < 0) return {-1, {}};
      push(x);
      Arc e = key[x];
      heap[u] = merge(merge, L[x], R[x]);
      if (heap[u] >= 0) lz[heap[u]] -= e.w; // reduced costs
      Q[qi] = e, path[qi++] = u, seen[u] = s;
      res += e.w, u = uf.find(e.a);
      if (seen[u] == s) { // cycle: contract it
        int cyc = -1, end = qi, time = uf.time();
        do cyc = merge(merge, cyc, heap[w = path[--qi]]);
        while (uf.join(u, w));
        u = uf.find(u), heap[u] = cyc, seen[u] = -1;
        cycs.push_front({u, time, {&Q[qi], &Q[end]}});
      }
    }
    rep(i, 0, qi) in[uf.find(Q[i].b)] = Q[i];
  }
  for (auto& [u, t, comp] : cycs) { // undo, fix the edges
    uf.rollback(t);
    Arc inE = in[u];
    for (auto& e : comp) in[uf.find(e.b)] = e;
    in[uf.find(inE.b)] = inE;
  }
  rep(i, 0, n) par[i] = in[i].a;
  return {res, par};
}
