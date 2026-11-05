#pragma once
// Brute-force helpers shared by graph tests.
inline int components(int n, const vector<pii>& es, int skipEdge = -1, int skipV = -1) {
  vi p(n);
  iota(all(p), 0);
  function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
  int c = n - (skipV >= 0);
  rep(i, 0, sz(es)) {
    auto [a, b] = es[i];
    if (i == skipEdge || a == skipV || b == skipV) continue;
    a = f(a), b = f(b);
    if (a != b) p[a] = b, --c;
  }
  return c;
}
// Max matching in a general graph by bitmask DP (n <= 16).
inline int bruteMatching(int n, const vector<pii>& es) {
  vector<int> adj(n);
  for (auto [a, b] : es) if (a != b) adj[a] |= 1 << b, adj[b] |= 1 << a;
  vector<int> dp(1 << n, -1);
  function<int(int)> go = [&](int m) {
    if (!m) return 0;
    int& r = dp[m];
    if (r >= 0) return r;
    int v = __builtin_ctz(m), rest = m & ~(1 << v);
    r = go(rest);
    for (int s = adj[v] & rest; s; s &= s - 1)
      r = max(r, 1 + go(rest & ~(s & -s)));
    return r;
  };
  return go((1 << n) - 1);
}
