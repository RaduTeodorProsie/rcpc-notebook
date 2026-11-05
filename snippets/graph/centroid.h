/**
 * Name: Centroid decomposition
 * Description: Calls `solve(c)` for every centroid, top-down.
 *   Inside, vertices with `removed` set belong to earlier levels,
 *   so a DFS from `c` that avoids them sees exactly the current
 *   component. `cpar` is the centroid tree. Uses: count paths of
 *   length at most $K$.
 * Time: $O(n log n)$ plus the work in `solve`
 */
#pragma once
struct Centroid {
  vector<vi> g;
  vi siz, cpar;
  vector<bool> removed;
  Centroid(const vector<vi>& g) : g(g), siz(sz(g)),
      cpar(sz(g), -1), removed(sz(g)) {}
  int calc(int v, int p) {
    siz[v] = 1;
    for (int u : g[v])
      if (u != p && !removed[u]) siz[v] += calc(u, v);
    return siz[v];
  }
  int find(int v, int p, int tot) {
    for (int u : g[v])
      if (u != p && !removed[u] && 2 * siz[u] > tot)
        return find(u, v, tot);
    return v;
  }
  template <class F>
  void build(F solve, int v = 0, int p = -1) {
    int c = find(v, -1, calc(v, -1));
    cpar[c] = p, solve(c), removed[c] = true;
    for (int u : g[c])
      if (!removed[u]) build(solve, u, c);
  }
};
// --- uses ---
ll pathsUpTo(const vector<vi>& g, int K) {
  Centroid cd(g);
  ll ans = 0;
  auto pairs = [&](vi& d) { // i < j, d_i + d_j <= K
    sort(all(d));
    ll r = 0;
    for (int i = 0, j = sz(d) - 1; i < j;)
      if (d[i] + d[j] <= K) r += j - i++;
      else --j;
    return r;
  };
  auto dfs = [&](auto& self, int v, int p, int d, vi& out)
      -> void {
    out.push_back(d);
    for (int u : g[v])
      if (u != p && !cd.removed[u])
        self(self, u, v, d + 1, out);
  };
  cd.build([&](int c) {
    vi every{0};
    for (int u : g[c])
      if (!cd.removed[u]) {
        vi sub;
        dfs(dfs, u, c, 1, sub);
        ans -= pairs(sub);
        every.insert(every.end(), all(sub));
      }
    ans += pairs(every);
  });
  return ans;
}
