#include "number-theory/sieve.h"
#include "testlib.h"
int main() {
  int N = 3000;
  Sieve s(N);
  int cnt = 0;
  rep(n, 1, N + 1) {
    int phi = 0;
    rep(i, 1, n + 1) phi += gcd(i, n) == 1;
    CHECK(s.phi[n] == phi, "n=%d", n);
    vector<pii> f;
    int x = n, mu = 1;
    for (int p = 2; p <= x; ++p)
      if (x % p == 0) {
        int e = 0;
        while (x % p == 0) x /= p, ++e;
        f.push_back({p, e});
        mu = e > 1 ? 0 : -mu;
      }
    CHECK(s.mu[n] == mu, "n=%d", n);
    CHECK(s.factor(n) == f, "n=%d", n);
    if (n > 1 && sz(f) == 1 && f[0].second == 1) {
      ++cnt;
      CHECK(s.lp[n] == n);
    }
  }
  CHECK(cnt == sz(s.pr));
}
