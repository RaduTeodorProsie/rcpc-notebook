#include "dp/aliens.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 25), k = rnd(1, n);
    vector<ll> a = rvec(n, 0, 10);
    vector<ll> s(n + 1);
    rep(i, 0, n) s[i + 1] = s[i] + a[i];
    const ll INF = LLONG_MAX / 4;
    vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INF));
    dp[0][0] = 0;
    rep(c, 1, k + 1) rep(i, 1, n + 1) rep(j, 0, i) if (dp[c - 1][j] < INF)
      dp[c][i] = min(dp[c][i], dp[c - 1][j] + (s[i] - s[j]) * (s[i] - s[j]));
    CHECK(splitK(a, k) == dp[k][n]);
  }
}
