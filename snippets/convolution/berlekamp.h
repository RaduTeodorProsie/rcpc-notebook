/**
 * Name: Berlekamp–Massey
 * Description: `berlekamp(s)` finds the shortest linear
 *   recurrence $s_i = c_1 s_(i-1) + dots + c_L s_(i-L)$ that holds
 *   for all of $s$ (mod a prime), and returns $c_1..c_L$. A
 *   recurrence of order $L$ is found from $2L$ terms, so: brute
 *   force the first few hundred terms of a sequence you suspect
 *   is linear (number of tilings or paths of a fixed-width grid,
 *   a DP whose state count does not depend on $n$, sums of
 *   powers), and check that $L$ is well below half of them.
 *   `linRec(s, c, n)` is then $s_n$, from $s_0..s_(L-1)$: it
 *   computes $x^n$ modulo $x^L - c_1 x^(L-1) - dots - c_L$
 *   (Kitamasa); if that remainder is $sum r_i x^i$, then
 *   $s_n = sum r_i s_i$.
 * Usage: auto c = berlekamp(first); // first 2L+ terms
 *   mint x = linRec(first, c, 1e18);
 * Time: `berlekamp` $O(|s|^2)$, `linRec` $O(L^2 log n)$
 */
#pragma once
#include "number-theory/modint.h"
vector<mint> berlekamp(const vector<mint>& s) {
  vector<mint> C{1}, B{1};
  mint b = 1;
  int L = 0, m = 1;
  rep(i, 0, sz(s)) {
    mint d = 0; // how far C is from predicting s_i
    rep(j, 0, L + 1) d += C[j] * s[i - j];
    if (d == 0) { ++m; continue; }
    vector<mint> T = C;
    mint k = d / b;
    C.resize(max(sz(C), sz(B) + m));
    rep(j, 0, sz(B)) C[j + m] -= k * B[j];
    if (2 * L <= i) L = i + 1 - L, B = T, b = d, m = 1;
    else ++m;
    C.resize(max(sz(C), L + 1));
  }
  vector<mint> c(L);
  rep(j, 0, L) c[j] = -C[j + 1];
  return c;
}
mint linRec(const vector<mint>& s, const vector<mint>& c,
            ll n) {
  int L = sz(c);
  if (!L) return 0;
  auto mul = [&](const vector<mint>& a,
                 const vector<mint>& b) {
    vector<mint> r(2 * L - 1);
    rep(i, 0, L) rep(j, 0, L) r[i + j] += a[i] * b[j];
    for (int i = 2 * L - 2; i >= L; --i) // x^L = sum c x^.
      rep(j, 0, L) r[i - 1 - j] += r[i] * c[j];
    r.resize(L);
    return r;
  };
  vector<mint> r(L), x(L);
  r[0] = 1;
  if (L == 1) x[0] = c[0];
  else x[1] = 1;
  for (; n; n >>= 1, x = mul(x, x))
    if (n & 1) r = mul(r, x);
  mint ans = 0;
  rep(i, 0, L) ans += r[i] * s[i];
  return ans;
}
