/**
 * Name: Palindromic tree
 * Description: One node per distinct palindromic substring, plus
 *   roots $0$ (length $-1$) and $1$ (length $0$). After `add(c)`,
 *   `last` is the longest palindromic suffix. After `count()`,
 *   `occ[v]` is the number of occurrences of node $v$. Distinct
 *   palindromes: number of nodes $- 2$; all palindromic
 *   substrings: $sum o c c$. Suffix links only shorten, so
 *   `link[v]` $< v$: loops over $v = 2, 3, dots$ visit links first.
 * Time: $O(n Sigma)$
 */
#pragma once
struct Eertree {
  string s;
  vi len{-1, 0}, link{0, 0}, occ{0, 0};
  vector<array<int, 26>> nx{{}, {}}; //!
  int last = 1;
  int up(int v, int i) {
    while (i - 1 - len[v] < 0 || s[i - 1 - len[v]] != s[i])
      v = link[v];
    return v;
  }
  void add(char ch) {
    s += ch;
    int i = sz(s) - 1, c = ch - 'a', p = up(last, i); //!
    if (!nx[p][c]) {
      int q = up(link[p], i);
      len.push_back(len[p] + 2);
      link.push_back(len.back() == 1 ? 1 : nx[q][c]);
      occ.push_back(0), nx.emplace_back();
      nx[p][c] = sz(len) - 1;
    }
    occ[last = nx[p][c]]++;
  }
  void count() {
    for (int v = sz(len) - 1; v > 1; --v)
      occ[link[v]] += occ[v];
  }
};
// --- uses ---
// Number of palindromes ending at each position i: the
// palindromic suffixes of s[0..i], = depth of `last` along
// suffix links.
vi palEnds(const string& s) {
  Eertree t;
  vi r;
  for (char c : s) t.add(c), r.push_back(t.last);
  vi dep(sz(t.len));
  rep(v, 2, sz(t.len)) dep[v] = dep[t.link[v]] + 1;
  for (int& v : r) v = dep[v];
  return r;
}
// Fewest palindromes that s splits into. The palindromic
// suffixes of a prefix form O(log n) runs whose lengths
// differ by the same d; `sl` jumps to the next run, and
// `ser[v]` keeps the best dp over the run ending at v.
int minPalSplit(const string& s) {
  Eertree t;
  int n = sz(s);
  vi last(n);
  rep(i, 0, n) t.add(s[i]), last[i] = t.last;
  int m = sz(t.len);
  vi d(m), sl(m), ser(m), dp(n + 1, n);
  rep(v, 2, m) {
    int u = t.link[v];
    d[v] = t.len[v] - t.len[u];
    sl[v] = d[v] == d[u] ? sl[u] : u;
  }
  dp[0] = 0;
  rep(i, 1, n + 1)
    for (int v = last[i - 1]; t.len[v] > 0; v = sl[v]) {
      ser[v] = dp[i - t.len[sl[v]] - d[v]];
      if (d[v] == d[t.link[v]])
        ser[v] = min(ser[v], ser[t.link[v]]);
      dp[i] = min(dp[i], ser[v] + 1);
    }
  return dp[n];
}
