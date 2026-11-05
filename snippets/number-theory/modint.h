/**
 * Name: Modular integer
 * Description: Arithmetic modulo a prime `MOD` (`inv` uses
 *   Fermat).
 */
#pragma once
const int MOD = 998244353; //!
struct mint {
  int v;
  mint(ll x = 0) : v(int((x % MOD + MOD) % MOD)) {}
  mint& operator+=(mint o) {
    if ((v += o.v) >= MOD) v -= MOD;
    return *this;
  }
  mint& operator-=(mint o) {
    if ((v -= o.v) < 0) v += MOD;
    return *this;
  }
  mint& operator*=(mint o) {
    v = int((ll)v * o.v % MOD);
    return *this;
  }
  mint& operator/=(mint o) { return *this *= o.inv(); }
  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
  friend mint operator/(mint a, mint b) { return a /= b; }
  mint operator-() const { return mint() - *this; }
  bool operator==(mint o) const { return v == o.v; }
  mint pow(ll e) const {
    mint r = 1, b = *this;
    for (; e; e >>= 1, b *= b)
      if (e & 1) r *= b;
    return r;
  }
  mint inv() const { return pow(MOD - 2); }
};
// --- uses ---
// Binomials: call initFact(max n) once.
vector<mint> fact, ifact;
void initFact(int n) {
  fact.assign(n + 1, 1), ifact.assign(n + 1, 1);
  rep(i, 1, n + 1) fact[i] = fact[i - 1] * i;
  ifact[n] = fact[n].inv();
  for (int i = n; i > 0; --i) ifact[i - 1] = ifact[i] * i;
}
mint binom(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fact[n] * ifact[k] * ifact[n - k];
}
