/**
 * Name: Number theoretic transform
 * Description: `conv<M>(a, b)` multiplies polynomials modulo a
 *   prime $M = c dot 2^k + 1$ with primitive root $3$ ($998244353$,
 *   $167772161$, $469762049$), needs $2^k >= |a| + |b|$. Uses:
 *   product modulo any $m$, or exact up to $10^26$, by CRT.
 * Time: $O(n log n)$
 */
#pragma once
template <int M> ll pw(ll b, ll e) {
  ll r = 1;
  for (b %= M; e; e >>= 1, b = b * b % M)
    if (e & 1) r = r * b % M;
  return r;
}
template <int M> void ntt(vector<ll>& a, bool inv) {
  int n = sz(a);
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    ll w = pw<M>(3, (M - 1) / len);
    if (inv) w = pw<M>(w, M - 2);
    for (int i = 0; i < n; i += len) {
      ll wn = 1;
      rep(j, 0, len / 2) {
        ll &x = a[i + j], &y = a[i + j + len / 2];
        ll u = x, v = y * wn % M;
        x = u + v < M ? u + v : u + v - M;
        y = u - v >= 0 ? u - v : u - v + M;
        wn = wn * w % M;
      }
    }
  }
  if (inv) {
    ll ni = pw<M>(n, M - 2);
    for (ll& x : a) x = x * ni % M;
  }
}
template <int M>
vector<ll> conv(vector<ll> a, vector<ll> b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, n = 1;
  while (n < s) n <<= 1;
  for (ll& x : a) x = (x % M + M) % M;
  for (ll& x : b) x = (x % M + M) % M;
  a.resize(n), b.resize(n);
  ntt<M>(a, 0), ntt<M>(b, 0);
  rep(i, 0, n) a[i] = a[i] * b[i] % M;
  ntt<M>(a, 1);
  a.resize(s);
  return a;
}
// --- uses ---
vector<ll> convMod(const vector<ll>& a, const vector<ll>& b,
                   ll m) {
  const int P0 = 998244353, P1 = 167772161, P2 = 469762049;
  auto x = conv<P0>(a, b), y = conv<P1>(a, b),
       z = conv<P2>(a, b);
  ll i01 = pw<P1>(P0, P1 - 2);
  ll i012 = pw<P2>((ll)P0 * P1 % P2, P2 - 2);
  vector<ll> r(sz(x));
  rep(i, 0, sz(x)) {
    ll t1 = (y[i] - x[i] % P1 + P1) % P1 * i01 % P1;
    ll v01 = x[i] + P0 * t1; // exact value mod P0*P1
    ll t2 = (z[i] - v01 % P2 + P2) % P2 * i012 % P2;
    r[i] = (v01 % m + (__int128)P0 * P1 % m * t2) % m;
  }
  return r;
}
