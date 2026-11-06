/**
 * Name: FFT
 * Description: Convolution with complex doubles. Rounded results
 *   are exact while $|"result"| lt.tilde 10^15$; use NTT otherwise.
 * Time: $O(n log n)$
 */
#pragma once
using cd = complex<double>;
void fft(vector<cd>& a, bool inv) {
  int n = sz(a);
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    vector<cd> w(len / 2);
    rep(j, 0, len / 2) {
      long double t = 2 * acosl(-1) * j / len;
      if (inv) t = -t;
      w[j] = cd(cosl(t), sinl(t));
    }
    for (int i = 0; i < n; i += len)
      rep(j, 0, len / 2) {
        cd u = a[i + j], v = a[i + j + len / 2] * w[j];
        a[i + j] = u + v, a[i + j + len / 2] = u - v;
      }
  }
  if (inv)
    for (cd& x : a) x /= n;
}
vector<ll> fconv(const vector<ll>& a, const vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, n = 1;
  while (n < s) n <<= 1;
  vector<cd> fa(all(a)), fb(all(b));
  fa.resize(n), fb.resize(n);
  fft(fa, 0), fft(fb, 0);
  rep(i, 0, n) fa[i] *= fb[i];
  fft(fa, 1);
  vector<ll> r(s);
  rep(i, 0, s) r[i] = llround(fa[i].real());
  return r;
}
