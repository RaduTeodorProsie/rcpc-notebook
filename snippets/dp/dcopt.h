/**
 * Name: Divide and conquer DP
 * Description: Fills $d p[i] = min_(k < i) (p r e v[k] + C(k, i))$
 *   for $i in [l o, h i)$, when the best $k$ is non-decreasing in
 *   $i$ (true if $C$ satisfies the quadrangle inequality).
 *   Call once per layer: `dc(1, n + 1, 0, n, C, prev, dp)`.
 *   Unreachable states: `prev[k]` $>= 10^18$.
 * Time: $O(n log n)$ evaluations of $C$ per layer
 */
#pragma once
template <class F>
void dc(int lo, int hi, int klo, int khi, F& C,
        const vector<ll>& prev, vector<ll>& dp) {
  const ll INF = 1e18;
  if (lo >= hi) return;
  int mid = (lo + hi) / 2, best = klo;
  dp[mid] = INF;
  rep(k, klo, min(mid - 1, khi) + 1) {
    ll v = prev[k] >= INF ? INF : prev[k] + C(k, mid);
    if (v < dp[mid]) dp[mid] = v, best = k;
  }
  dc(lo, mid, klo, best, C, prev, dp);
  dc(mid + 1, hi, best, khi, C, prev, dp);
}
