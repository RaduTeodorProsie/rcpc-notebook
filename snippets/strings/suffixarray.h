/**
 * Name: Suffix array
 * Description: `sa` lists the suffixes of $s$ in sorted order.
 *   `lcp[i]` is the LCP of suffixes `sa[i]` and `sa[i+1]`.
 *   $s$ must not contain `'\0'`.
 * Time: $O(n log n)$
 */
#pragma once
vi suffixArray(string s) {
  s += '\0';
  int n = sz(s);
  vi sa(n), c(n), tmp(n), cnt(max(256, n));
  for (char ch : s) cnt[(unsigned char)ch]++;
  partial_sum(all(cnt), cnt.begin());
  rep(i, 0, n) sa[--cnt[(unsigned char)s[i]]] = i;
  rep(i, 1, n)
    c[sa[i]] = c[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
  for (int k = 1; k < n && c[sa[n - 1]] < n - 1; k <<= 1) {
    rep(i, 0, n) tmp[i] = (sa[i] - k + n) % n;
    fill(all(cnt), 0);
    rep(i, 0, n) cnt[c[i]]++;
    partial_sum(all(cnt), cnt.begin());
    for (int i = n - 1; i >= 0; --i)
      sa[--cnt[c[tmp[i]]]] = tmp[i];
    vi nc(n);
    rep(i, 1, n) {
      pii a = {c[sa[i]], c[(sa[i] + k) % n]};
      pii b = {c[sa[i - 1]], c[(sa[i - 1] + k) % n]};
      nc[sa[i]] = nc[sa[i - 1]] + (a != b);
    }
    c = nc;
  }
  sa.erase(sa.begin());
  return sa;
}
vi lcpArray(const string& s, const vi& sa) {
  int n = sz(s), h = 0;
  vi rk(n), lcp(max(n - 1, 0));
  rep(i, 0, n) rk[sa[i]] = i;
  rep(i, 0, n) {
    if (rk[i] == n - 1) { h = 0; continue; }
    int j = sa[rk[i] + 1];
    while (max(i, j) + h < n && s[i + h] == s[j + h]) ++h;
    lcp[rk[i]] = h;
    if (h) --h;
  }
  return lcp;
}
// --- uses ---
// Number of distinct non-empty substrings.
ll distinctSubstrings(const string& s) {
  vi lcp = lcpArray(s, suffixArray(s));
  ll n = sz(s), r = n * (n + 1) / 2;
  for (int x : lcp) r -= x;
  return r;
}
// Longest common substring: (length, start in s).
pii commonSubstring(const string& s, const string& t) {
  string u = s + '\1' + t;
  vi sa = suffixArray(u), lcp = lcpArray(u, sa);
  int n = sz(s);
  pii best{0, 0};
  rep(i, 0, sz(lcp)) {
    int a = sa[i], b = sa[i + 1];
    if ((a < n) != (b < n))
      best = max(best, {lcp[i], a < n ? a : b});
  }
  return best;
}
#include "data-structures/sparsetable.h"
struct SuffixLCP { // LCP of suffixes i and j in O(1)
  int n;
  vi sa, rk;
  RMQ<int> rmq;
  SuffixLCP(const string& s) : n(sz(s)), sa(suffixArray(s)),
      rk(n), rmq(lcpArray(s, sa)) {
    rep(i, 0, n) rk[sa[i]] = i;
  }
  int lcp(int i, int j) {
    if (i == j) return n - i;
    int a = rk[i], b = rk[j];
    if (a > b) swap(a, b);
    return rmq.query(a, b);
  }
};
