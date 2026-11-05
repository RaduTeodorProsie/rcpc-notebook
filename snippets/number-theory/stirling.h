/**
 * Name: Stirling and Bell rows
 * Description: For one $n$: all $S(n, k)$, $k = 0..n$, as one
 *   convolution of the inclusion–exclusion formula; all unsigned
 *   $c(n, k)$ as the coefficients of $product_(i=l)^(r-1) (x + i)$
 *   with $l = 0, r = n$; and $B_n = sum_k S(n, k)$. All modulo the
 *   NTT prime `MS`.
 * Time: $O(n log n)$; $O(n log^2 n)$
 */
#pragma once
#include "ntt.h"
const int MS = 998244353; //!
vector<ll> stirling2(int n) {
  vector<ll> f(n + 1, 1), a(n + 1), b(n + 1);
  rep(i, 1, n + 1) f[i] = f[i - 1] * i % MS;
  rep(i, 0, n + 1) {
    ll inv = pw<MS>(f[i], MS - 2);
    a[i] = i & 1 ? MS - inv : inv; // (-1)^i / i!
    b[i] = pw<MS>(i, n) * inv % MS; // i^n / i!
  }
  auto c = conv<MS>(a, b);
  c.resize(n + 1);
  return c;
}
vector<ll> stirling1(int l, int r) {
  if (l >= r) return {1};
  if (r - l == 1) return {l, 1};
  int m = (l + r) / 2;
  return conv<MS>(stirling1(l, m), stirling1(m, r));
}
ll bell(int n) {
  ll s = 0;
  for (ll x : stirling2(n)) s += x;
  return s % MS;
}
