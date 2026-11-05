/**
 * Name: Berlekamp-Massey
 * Description: Shortest recurrence $s_i = sum_j c_j s_(i-1-j)$
 *   matching the given terms (give at least $2L$ terms). Uses:
 *   `kth` evaluates term $k$ in $O(L^2 log k)$.
 * Time: $O(n^2)$
 */
#pragma once
#include "modint.h"
vector<mint> berlekampMassey(const vector<mint>& s) {
  int N = sz(s), L = 0, m = 1;
  vector<mint> C(N + 1), B(N + 1);
  C[0] = B[0] = 1;
  mint b = 1;
  rep(n, 0, N) {
    mint d = 0;
    rep(i, 0, L + 1) d += C[i] * s[n - i];
    if (d == 0) { ++m; continue; }
    vector<mint> T = C;
    mint coef = d / b;
    rep(i, m, N + 1) C[i] -= coef * B[i - m];
    if (2 * L <= n) L = n + 1 - L, B = T, b = d, m = 1;
    else ++m;
  }
  vector<mint> c(L);
  rep(i, 0, L) c[i] = -C[i + 1];
  return c;
}
// --- uses ---
mint kth(const vector<mint>& s, const vector<mint>& c,
         ll k) {
  int L = sz(c);
  if (!L) return 0;
  auto mul = [&](const vector<mint>& a,
                 const vector<mint>& b) {
    vector<mint> r(2 * L);
    rep(i, 0, L) rep(j, 0, L) r[i + j] += a[i] * b[j];
    for (int i = 2 * L - 1; i >= L; --i)
      rep(j, 0, L) r[i - 1 - j] += r[i] * c[j];
    r.resize(L);
    return r;
  };
  vector<mint> res(L), x(L);
  res[0] = 1;
  if (L > 1) x[1] = 1;
  else x[0] = c[0];
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  mint ans = 0;
  rep(i, 0, L) ans += res[i] * s[i];
  return ans;
}
