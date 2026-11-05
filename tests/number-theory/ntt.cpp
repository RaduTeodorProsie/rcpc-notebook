#include "number-theory/ntt.h"
#include "testlib.h"
vector<__int128> naive(const vector<ll>& a, const vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  vector<__int128> r(sz(a) + sz(b) - 1);
  rep(i, 0, sz(a)) rep(j, 0, sz(b)) r[i + j] += (__int128)a[i] * b[j];
  return r;
}
int main() {
  const int M = 998244353;
  rep(it, 0, 300) {
    int n = rnd(0, 300), m = rnd(0, 300);
    auto a = rvec(n, -1e9, 1e9), b = rvec(m, 0, 1e9);
    auto w = naive(a, b);
    auto r = conv<M>(a, b);
    CHECK(sz(r) == sz(w));
    rep(i, 0, sz(r)) CHECK(r[i] == (ll)((w[i] % M + M) % M));
    for (ll mod : {1000000007ll, 2ll, 1ll << 31}) {
      auto aa = a;
      for (ll& x : aa) x = (x % mod + mod) % mod;
      auto w2 = naive(aa, b);
      for (ll& x : b) x %= mod;
      auto r2 = convMod(aa, b, mod);
      rep(i, 0, sz(r2)) CHECK(r2[i] == (ll)(w2[i] % mod), "i=%d mod=%lld", i, mod);
    }
  }
  vector<ll> big(100000, 1e9 + 6);
  auto r = convMod(big, big, 1e9 + 7);
  CHECK(r[99999] == (ll)(((__int128)100000 % (ll)(1e9 + 7))));
}
