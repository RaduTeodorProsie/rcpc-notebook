/**
 * Name: Virtual tree
 * Description: Compresses the tree to the vertices in `vs` plus
 *   the LCAs of their pairs (fewer than $2k$ vertices): the parent
 *   of each is its nearest proper ancestor among them. Returns
 *   `(v, parent)` pairs, no duplicates, sorted by `tin`. The first
 *   pair is the root, with parent $-1$, and every parent comes
 *   before its children: loop backwards for a bottom-up DP. The
 *   compressed edge stands for a path of `dep[v] - dep[parent]`
 *   original edges.
 * Usage: for (auto [v, p] : virtualTree(t, vs)) ...
 * Time: $O(k log n)$
 */
#pragma once
#include "lca.h"
vector<pii> virtualTree(LCA& t, vi vs) {
  auto cmp = [&](int a, int b) {
    return t.tin[a] < t.tin[b];
  };
  sort(all(vs), cmp);
  int k = sz(vs);
  rep(i, 0, k - 1) vs.push_back(t.lca(vs[i], vs[i + 1]));
  sort(all(vs), cmp);
  vs.erase(unique(all(vs)), vs.end());
  vector<pii> res;
  vi st;
  for (int v : vs) {
    while (sz(st) && !t.anc(st.back(), v)) st.pop_back();
    res.push_back({v, sz(st) ? st.back() : -1});
    st.push_back(v);
  }
  return res;
}
