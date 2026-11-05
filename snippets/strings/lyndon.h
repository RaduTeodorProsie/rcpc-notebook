/**
 * Name: Lyndon, minimal rotation
 * Description: `duval` splits $s = w_1 w_2 dots$ with
 *   $w_1 >= w_2 >= dots$, each strictly smaller than all of its
 *   proper suffixes; returns the start of each $w_i$.
 *   `minRotation` is the start of the smallest rotation.
 * Time: $O(n)$
 */
#pragma once
vi duval(const string& s) {
  int n = sz(s), i = 0;
  vi res;
  while (i < n) {
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j])
      k = s[k] < s[j] ? i : k + 1, ++j;
    while (i <= k) res.push_back(i), i += j - k;
  }
  return res;
}
int minRotation(const string& s) {
  string t = s + s;
  int n = sz(s), i = 0, ans = 0;
  while (i < n) {
    ans = i;
    int j = i + 1, k = i;
    while (j < 2 * n && t[k] <= t[j])
      k = t[k] < t[j] ? i : k + 1, ++j;
    while (i <= k) i += j - k;
  }
  return ans;
}
