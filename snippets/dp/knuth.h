/**
 * Name: Knuth optimization
 * Description: Interval DP $d p[i][j] = w(i, j) + min_(i<k<j)
 *   (d p[i][k] + d p[k][j])$, $d p[i][i+1] = 0$, when
 *   $o p t[i][j-1] <= o p t[i][j] <= o p t[i+1][j]$ (holds if $w$
 *   satisfies the quadrangle inequality and is monotone).
 *   Returns $d p[0][n]$.
 * Time: $O(n^2)$
 */
#pragma once
template <class W> ll knuth(int n, W w) {
  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
  vector<vi> opt(n + 1, vi(n + 1));
  rep(i, 0, n) opt[i][i + 1] = i + 1;
  rep(len, 2, n + 1) rep(i, 0, n - len + 1) {
    int j = i + len;
    dp[i][j] = LLONG_MAX;
    rep(k, opt[i][j - 1], opt[i + 1][j] + 1) {
      if (k <= i || k >= j) continue;
      ll v = dp[i][k] + dp[k][j] + w(i, j);
      if (v < dp[i][j]) dp[i][j] = v, opt[i][j] = k;
    }
  }
  return dp[0][n];
}
