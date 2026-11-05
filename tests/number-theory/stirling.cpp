#include "number-theory/stirling.h"
#include "testlib.h"
int main() {
  const int N = 300;
  vector<vector<ll>> S(N + 1, vector<ll>(N + 1)), c = S;
  S[0][0] = c[0][0] = 1;
  rep(n, 1, N + 1) rep(k, 1, n + 1) {
    S[n][k] = (S[n - 1][k - 1] + k * S[n - 1][k]) % MS;
    c[n][k] = (c[n - 1][k - 1] + (n - 1) * c[n - 1][k]) % MS;
  }
  for (int n : {0, 1, 2, 3, 5, 10, 37, 100, 255, 300}) {
    auto s2 = stirling2(n), s1 = stirling1(0, n);
    CHECK(sz(s2) == n + 1 && sz(s1) == n + 1, "n=%d", n);
    rep(k, 0, n + 1) CHECK(s2[k] == S[n][k] && s1[k] == c[n][k], "n=%d k=%d", n, k);
    ll b = 0;
    rep(k, 0, n + 1) b += S[n][k];
    CHECK(bell(n) == b % MS);
  }
  CHECK(bell(5) == 52 && bell(10) == 115975);
}
