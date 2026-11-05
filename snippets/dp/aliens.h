/**
 * Name: Lagrangian relaxation (Aliens)
 * Description: For "minimum cost using exactly $k$ items (groups,
 *   segments, ...)" when $"opt"(k)$ is convex in $k$ (its
 *   differences grow; check with a brute force). Remove the
 *   limit and charge $lambda$ per item instead: $g(lambda) =
 *   min_j ("opt"(j) + lambda j)$ is a DP without the $k$
 *   dimension. A larger $lambda$ means fewer items. `solve(l)`
 *   returns (cost including $l$ per item, items), taking the
 *   fewest items among equal costs; the binary search finds the
 *   smallest $lambda$ with at most $k$ items, and then
 *   $"opt"(k) = g(lambda) - lambda k$, also when the DP used fewer
 *   (those counts tie with $k$ at this $lambda$). Needs integer
 *   costs; $[l o, h i]$ must contain $-C..C$ where $C$ exceeds every
 *   $|"opt"(j) - "opt"(j-1)|$. Maximum: negate the costs.
 * Time: $O(log C)$ calls to `solve`
 */
#pragma once
template <class F> ll aliens(F solve, int k, ll lo, ll hi) {
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    if (solve(mid).second <= k) hi = mid;
    else lo = mid + 1;
  }
  return solve(lo).first - lo * k;
}
// --- uses ---
// Split a (values >= 0) into exactly k segments,
// minimizing the sum of squared segment sums; each
// segment costs l extra.
ll splitK(const vector<ll>& a, int k) {
  int n = sz(a);
  vector<ll> s(n + 1);
  rep(i, 0, n) s[i + 1] = s[i] + a[i];
  auto solve = [&](ll l) {
    vector<pair<ll, int>> dp(n + 1, {LLONG_MAX, 0});
    dp[0] = {0, 0};
    rep(i, 1, n + 1) rep(j, 0, i) {
      ll d = s[i] - s[j];
      dp[i] = min(dp[i], {dp[j].first + d * d + l,
                          dp[j].second + 1});
    }
    return dp[n];
  };
  ll C = s[n] * s[n] + 1;
  return aliens(solve, k, -C, C);
}
