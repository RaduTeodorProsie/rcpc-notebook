#include "number-theory/modint.h"
#include "testlib.h"
int main() {
  initFact(2000);
  vector<vector<mint>> C(201, vector<mint>(201));
  rep(n, 0, 201) {
    C[n][0] = 1;
    rep(k, 1, n + 1) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    rep(k, -2, n + 3) CHECK(binom(n, k) == (k < 0 || k > n ? 0 : C[n][k]));
  }
  rep(it, 0, 10000) {
    ll a = rnd(-ll(1e18), ll(1e18)), b = rnd(1, MOD - 1);
    mint x = a, y = b;
    CHECK((x / y) * y == x);
    CHECK(x - y + y == x && -x + x == 0);
    __int128 r = ((__int128)a % MOD + MOD) % MOD;
    CHECK(x.v == (int)r);
    ll e = rnd(0, 50), p = 1;
    rep(i, 0, e) p = p * (r % MOD) % MOD;
    CHECK(x.pow(e).v == p);
  }
}
