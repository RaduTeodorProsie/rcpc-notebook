/**
 * Name: Palindromic tree
 * Description: One node per distinct palindromic substring, plus
 *   roots $0$ (length $-1$) and $1$ (length $0$). After `add(c)`,
 *   `last` is the longest palindromic suffix. After `count()`,
 *   `occ[v]` is the number of occurrences of node $v$. Distinct
 *   palindromes: number of nodes $- 2$; all palindromic
 *   substrings: $sum o c c$.
 * Time: $O(n Sigma)$
 */
#pragma once
struct Eertree {
  string s;
  vi len{-1, 0}, link{0, 0}, occ{0, 0};
  vector<array<int, 26>> nx{{}, {}};
  int last = 1;
  int up(int v, int i) {
    while (i - 1 - len[v] < 0 || s[i - 1 - len[v]] != s[i])
      v = link[v];
    return v;
  }
  void add(char ch) {
    s += ch;
    int i = sz(s) - 1, c = ch - 'a', p = up(last, i);
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
