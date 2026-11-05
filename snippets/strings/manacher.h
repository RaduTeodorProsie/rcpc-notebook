/**
 * Name: Manacher
 * Description: `d[0][i]`: number of odd palindromes centred
 *   at $i$. `d[1][i]`: number of even palindromes centred
 *   between $i-1$ and $i$.
 * Time: $O(n)$
 */
#pragma once
array<vi, 2> manacher(const string& s) {
  int n = sz(s);
  array<vi, 2> d = {vi(n), vi(n)};
  rep(z, 0, 2) for (int i = 0, l = 0, r = -1; i < n; ++i) {
    int k = i > r ? !z
                  : min(d[z][l + r - i + z], r - i + 1);
    while (i - k - z >= 0 && i + k < n &&
           s[i - k - z] == s[i + k])
      ++k;
    d[z][i] = k--;
    if (i + k > r) l = i - k - z, r = i + k;
  }
  return d;
}
