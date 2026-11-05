/**
 * Name: Z-function
 * Description: `z[i]` is the longest common prefix of $s$ and
 *   $s[i..]$, with `z[0]` $= 0$.
 * Time: $O(n)$
 */
#pragma once
vi zfunc(const string& s) {
  int n = sz(s), l = 0, r = 0;
  vi z(n);
  rep(i, 1, n) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}
