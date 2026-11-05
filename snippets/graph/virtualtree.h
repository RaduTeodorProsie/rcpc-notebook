/**
 * Name: Virtual tree
 * Description: The tree on the given vertices and their pairwise
 *   LCAs, as (vertex, parent) pairs in DFS order; the first one
 *   is the root, with parent $-1$. Fewer than $2k$ vertices; run
 *   the DP on it instead of the whole tree.
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
