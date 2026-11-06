#include "dp/aliens.h"
#include "testlib.h"
// opt[j], j = 0..n: split a into exactly j segments, each costing
// (segment sum)^2 + P. Convex in j for any P (P only adds a linear term).
vector<ll> bruteOpt(const vector<ll>& a, ll P) {
  int n = sz(a);
  vector<ll> s(n + 1);
  rep(i, 0, n) s[i + 1] = s[i] + a[i];
  const ll INF = LLONG_MAX / 4;
  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, INF));
  dp[0][0] = 0;
  rep(c, 1, n + 1) rep(i, 1, n + 1) rep(j, 0, i) if (dp[c - 1][j] < INF)
    dp[c][i] = min(dp[c][i], dp[c - 1][j] + (s[i] - s[j]) * (s[i] - s[j]) + P);
  vector<ll> opt(n + 1);
  rep(c, 0, n + 1) opt[c] = dp[c][n];
  return opt;
}
int main() {
  rep(it, 0, 1500) {
    int n = rnd(1, 14), k = rnd(1, n);
    ll big = it < 1200 ? (rnd(0, 1) ? 3 : 20) : 90000000;  // last ones: n s^2 near 9e18
    if (big > 100) n = rnd(1, 10), k = rnd(1, n);
    vector<ll> a = rvec(n, 0, big);
    ll P = big > 100 ? 0 : rnd(-400, 400);
    vector<ll> s(n + 1);
    rep(i, 0, n) s[i + 1] = s[i] + a[i];
    // minimum: {min cost + l * segments, segments}, ties towards fewer segments
    auto solveMin = [&](ll l) {
      vector<pair<ll, int>> dp(n + 1, {LLONG_MAX, 0});
      dp[0] = {0, 0};
      rep(i, 1, n + 1) rep(j, 0, i) {
        ll d = s[i] - s[j];
        dp[i] = min(dp[i], {dp[j].first + d * d + P + l, dp[j].second + 1});
      }
      return dp[n];
    };
    // maximum of value = -cost: {max value - l * segments, segments}, ties towards fewer
    auto solveMax = [&](ll l) {
      vector<pair<ll, int>> dp(n + 1, {LLONG_MIN, 0});
      dp[0] = {0, 0};
      rep(i, 1, n + 1) rep(j, 0, i) {
        ll d = s[i] - s[j];
        pair<ll, int> cand{dp[j].first - d * d - P - l, dp[j].second + 1};
        if (cand.first > dp[i].first || (cand.first == dp[i].first && cand.second < dp[i].second))
          dp[i] = cand;
      }
      return dp[n];
    };
    auto opt = bruteOpt(a, P);
    rep(j, 2, n + 1) CHECK(opt[j] - opt[j - 1] >= opt[j - 1] - opt[j - 2]);  // convex
    ll C = s[n] * s[n] + llabs(P) + 1;
    if (big > 100) C = s[n] * s[n] + 1;  // P = 0: cost never grows with segments
    ll minMost = *min_element(opt.begin() + 1, opt.begin() + k + 1);
    ll minLeast = *min_element(opt.begin() + k, opt.end());
    if (big <= 100) CHECK(aliens(solveMin, k, -C, C) == opt[k], "it=%d exact", it);
    CHECK(minAtMost(solveMin, k, C) == minMost, "it=%d min at most", it);
    CHECK(maxAtMost(solveMax, k, C) == -minMost, "it=%d max at most", it);
    if (big <= 100) {  // -C * n would overflow at the large sizes
      CHECK(minAtLeast(solveMin, k, C) == minLeast, "it=%d min at least", it);
      CHECK(maxAtLeast(solveMax, k, C) == -minLeast, "it=%d max at least", it);
    }
  }
}
