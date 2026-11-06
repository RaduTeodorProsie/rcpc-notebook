/**
 * Name: Polynomial inverse and division
 * Description: Coefficients in $[0, M)$, lowest degree first.
 *   `inverse<M>(a, n)` is the first $n$ coefficients of the power
 *   series $1\/a$ ($a_0 != 0$). Newton's method: if $a b equiv 1$
 *   mod $x^k$, then $b' = b(2 - a b)$ is right mod $x^(2k)$, so
 *   each round doubles the number of correct terms. Power series
 *   $p\/q$: `conv(p, inverse(q, n))`. `divMod<M>(a, b)` is $(q, r)$
 *   with $a = q b + r$, $deg r < deg b$; the last coefficient of
 *   $b$ must be nonzero. Reversing the coefficient order turns
 *   $a = q b + r$ into a statement mod $x^(deg a - deg b + 1)$
 *   where $r$ vanishes, so $"rev"(q) = "rev"(a) \/ "rev"(b)$ there.
 * Time: $O(n log n)$
 */
#pragma once
#include "ntt.h"
template <int M>
vector<ll> inverse(const vector<ll>& a, int n) {
  vector<ll> b{pw<M>(a[0], M - 2)};
  for (int k = 1; k < n; k *= 2) {
    vector<ll> f(a.begin(), a.begin() + min(sz(a), 2 * k));
    vector<ll> t = conv<M>(conv<M>(b, b), f);
    t.resize(2 * k), b.resize(2 * k);
    rep(i, 0, 2 * k) b[i] = ((2 * b[i] - t[i]) % M + M) % M;
  }
  b.resize(n);
  return b;
}
template <int M> pair<vector<ll>, vector<ll>>
divMod(const vector<ll>& a, const vector<ll>& b) {
  int n = sz(a), m = sz(b);
  if (n < m) return {{}, a};
  vector<ll> ra(a.rbegin(), a.rend()),
      rb(b.rbegin(), b.rend());
  ra.resize(n - m + 1);
  vector<ll> q = conv<M>(ra, inverse<M>(rb, n - m + 1));
  q.resize(n - m + 1), reverse(all(q));
  vector<ll> qb = conv<M>(q, b), r(m - 1);
  rep(i, 0, m - 1) r[i] = (a[i] - qb[i] + M) % M;
  return {q, r};
}
