/**
 * Name: Lagrangian relaxation (Aliens)
 * Description: Min cost with exactly $k$ items. `solve(l)` returns
 *   ($g(l)$, count): the min cost when each item costs $l$ extra,
 *   and its number of items, *ties broken towards fewer items*
 *   (compare (cost, count) pairs). Caveats: \
 *   – $"opt"(k)$ must be convex in $k$: check with a brute force. \
 *   – Return $g(lambda) - lambda k$ with the target $k$, not with
 *   the count `solve` reports: at the final $lambda$ several counts
 *   tie, and the reported one can be smaller than $k$. \
 *   – At most / at least $k$: if the optimum with no limit
 *   ($lambda = 0$) obeys the bound, it is the answer; otherwise the
 *   best uses exactly $k$. \
 *   – Integer costs; $[l o, h i]$ must contain $-C..C$, $C$ above
 *   every $|"opt"(j) - "opt"(j-1)|$. Maximum: negate the costs.
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
