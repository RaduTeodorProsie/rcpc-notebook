/**
 * Name: Suffix automaton
 * Description: Minimal automaton of all substrings of $s$. State
 *   $0$ is the empty string; `len[v]` is the longest string of
 *   state $v$, `link[v]` its suffix link. After `countOcc`,
 *   `cnt[v]` is the number of occurrences of each string of $v$.
 *   Each state is a set of substrings with the same end
 *   positions; their lengths are $(l e n_(l i n k), l e n]$.
 * Time: $O(n Sigma)$
 */
#pragma once
struct SAM {
  vi len, link, cnt;
  vector<array<int, 26>> nx; //!
  int last = 0;
  SAM(const string& s) {
    node(0, -1);
    for (char c : s) extend(c - 'a'); //!
  }
  int node(int l, int lk) {
    len.push_back(l), link.push_back(lk), cnt.push_back(0);
    nx.emplace_back().fill(-1);
    return sz(len) - 1;
  }
  void extend(int c) {
    int cur = node(len[last] + 1, 0), p = last;
    cnt[cur] = 1;
    for (; p >= 0 && nx[p][c] < 0; p = link[p])
      nx[p][c] = cur;
    if (p >= 0) {
      int q = nx[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int cl = node(len[p] + 1, link[q]);
        nx[cl] = nx[q];
        for (; p >= 0 && nx[p][c] == q; p = link[p])
          nx[p][c] = cl;
        link[q] = link[cur] = cl;
      }
    }
    last = cur;
  }
  void countOcc() {
    vi ord(sz(len));
    iota(all(ord), 0);
    sort(all(ord), [&](int a, int b) {
      return len[a] > len[b];
    });
    for (int v : ord)
      if (link[v] >= 0) cnt[link[v]] += cnt[v];
  }
};
// --- uses ---
// Number of distinct non-empty substrings.
ll distinct(SAM& a) {
  ll r = 0;
  rep(v, 1, sz(a.len)) r += a.len[v] - a.len[a.link[v]];
  return r;
}
int occurrences(SAM& a, const string& t) { // after countOcc
  int v = 0;
  for (char c : t)
    if ((v = a.nx[v][c - 'a']) < 0) return 0;
  return a.cnt[v];
}
int longestCommon(SAM& a, const string& t) {
  int v = 0, l = 0, best = 0;
  for (char ch : t) {
    int c = ch - 'a';
    while (v && a.nx[v][c] < 0) v = a.link[v], l = a.len[v];
    if (a.nx[v][c] >= 0) v = a.nx[v][c], ++l;
    best = max(best, l);
  }
  return best;
}
string kthDistinct(SAM& a, ll k) { // 1-based, k <= distinct
  vector<ll> paths(sz(a.len), -1);
  auto dfs = [&](auto& self, int v) -> ll {
    if (paths[v] >= 0) return paths[v];
    ll r = 1;
    for (int u : a.nx[v]) if (u >= 0) r += self(self, u);
    return paths[v] = r;
  };
  dfs(dfs, 0);
  string res;
  for (int v = 0; k > 0;)
    rep(c, 0, 26) {
      int u = a.nx[v][c];
      if (u < 0) continue;
      if (paths[u] >= k) {
        res += char('a' + c), --k, v = u;
        break;
      }
      k -= paths[u];
    }
  return res;
}
