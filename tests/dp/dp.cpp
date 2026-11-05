#include "dp/dcopt.h"
#include "dp/knuth.h"
#include "dp/lis.h"
#include "dp/slope.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {  // split into K parts minimizing sum of (part sum)^2
    int n = rnd(1, 40), K = rnd(1, n);
    auto a = rvec(n, 0, 20);
    vector<ll> pre(n + 1);
    rep(i, 0, n) pre[i + 1] = pre[i] + a[i];
    auto C = [&](int k, int i) { ll s = pre[i] - pre[k]; return s * s; };
    vector<ll> prev(n + 1, INF), dp(n + 1);
    prev[0] = 0;
    vector<vector<ll>> B(K + 1, vector<ll>(n + 1, INF));
    B[0][0] = 0;
    rep(j, 1, K + 1) rep(i, 1, n + 1) rep(k, 0, i) if (B[j - 1][k] < INF)
      B[j][i] = min(B[j][i], B[j - 1][k] + C(k, i));
    rep(j, 1, K + 1) {
      dp.assign(n + 1, INF);
      dc(1, n + 1, 0, n, C, prev, dp);
      rep(i, 1, n + 1) CHECK(dp[i] == B[j][i], "j=%d i=%d", j, i);
      prev = dp;
      prev[0] = INF;
    }
  }
  rep(it, 0, 300) {  // optimal merge of stones
    int n = rnd(1, 40);
    auto a = rvec(n, 1, 100);
    vector<ll> pre(n + 1);
    rep(i, 0, n) pre[i + 1] = pre[i] + a[i];
    auto w = [&](int i, int j) { return pre[j] - pre[i]; };
    vector<vector<ll>> B(n + 1, vector<ll>(n + 1));
    rep(len, 2, n + 1) rep(i, 0, n - len + 1) {
      int j = i + len;
      B[i][j] = LLONG_MAX;
      rep(k, i + 1, j) B[i][j] = min(B[i][j], B[i][k] + B[k][j] + w(i, j));
    }
    CHECK(knuth(n, w) == B[0][n]);
  }
  rep(it, 0, 2000) {
    int n = rnd(0, 30);
    auto a = rvec(n, 0, 10);
    vi l = lis(a);
    vi best(n, 1);
    int want = 0;
    rep(i, 0, n) {
      rep(j, 0, i) if (a[j] < a[i]) best[i] = max(best[i], best[j] + 1);
      want = max(want, best[i]);
    }
    CHECK(sz(l) == want);
    rep(i, 1, sz(l)) CHECK(l[i - 1] < l[i] && a[l[i - 1]] < a[l[i]]);
  }
}
