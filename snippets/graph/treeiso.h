/**
 * Name: Tree isomorphism
 * Description: `rootedClass(g, v)` numbers the rooted tree hanging
 *   from $v$ so that two rooted trees get the same number iff they
 *   are isomorphic (children in any order). A class is the sorted
 *   list of the children's classes, numbered through the global
 *   map `cls`: exact (no hashing), and numbers from different
 *   trees can be compared. The class of every subtree: store the
 *   return value per vertex. `treeClass(g)` does the same for
 *   unrooted trees ($n >= 1$): it roots at the centroid, or at
 *   both if there are two, and keeps the smaller number.
 * Time: $O(n log n)$
 */
#pragma once
map<vi, int> cls; // sorted classes of the children -> class
int rootedClass(const vector<vi>& g, int v, int p = -1) {
  vi ch;
  for (int u : g[v])
    if (u != p) ch.push_back(rootedClass(g, u, v));
  sort(all(ch));
  return cls.try_emplace(ch, sz(cls)).first->second;
}
int treeClass(const vector<vi>& g) {
  int n = sz(g), best = INT_MAX;
  vi siz(n, 1);
  auto dfs = [&](auto& self, int v, int p) -> void {
    int big = 0; // largest piece left when v is removed
    for (int u : g[v])
      if (u != p) {
        self(self, u, v), siz[v] += siz[u];
        big = max(big, siz[u]);
      }
    if (2 * max(big, n - siz[v]) <= n) // v is a centroid
      best = min(best, rootedClass(g, v));
  };
  dfs(dfs, 0, -1);
  return best;
}
