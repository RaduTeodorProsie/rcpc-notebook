/**
 * Name: Subset convolution
 * Description: $c_m = sum_(s subset.eq m) a_s b_(m without s)$,
 *   i.e. over pairs of disjoint masks with union $m$ (size $2^n$).
 *   OR convolution would also count overlapping pairs; those
 *   have $|s| + |t| > |s union t|$. So split by popcount:
 *   $hat(a)_k$ = zeta transform of $a$ restricted to masks with $k$
 *   bits, multiply as polynomials in $k$
 *   ($hat(c)_k = sum_(i+j=k) hat(a)_i hat(b)_j$ pointwise), Möbius
 *   back, and read $c_m$ from the layer $k = |m|$. Use: DP over
 *   partitions of a set into parts, $f(m) = sum f(s) g(m without s)$
 *   layer by layer (exp of a set power series).
 * Time: $O(2^n n^2)$, memory $2 (n+1) 2^n$ values
 */
#pragma once
#include "number-theory/modint.h"
vector<mint> subsetConv(const vector<mint>& a,
                        const vector<mint>& b) {
  int N = sz(a);
  if (!N) return {};
  int n = __lg(N);
  vector<vector<mint>> A(n + 1, vector<mint>(N)), B = A;
  rep(m, 0, N) {
    int k = __builtin_popcount(m);
    A[k][m] = a[m], B[k][m] = b[m];
  }
  auto tr = [&](vector<mint>& f, int s) { // zeta / Möbius
    for (int h = 1; h < N; h *= 2)
      for (int i = 0; i < N; i += 2 * h)
        rep(m, i, i + h) f[m + h] += f[m] * s;
  };
  rep(k, 0, n + 1) tr(A[k], 1), tr(B[k], 1);
  vector<mint> t(n + 1);
  rep(m, 0, N) { // product of the polynomials in k, into A
    fill(all(t), 0);
    rep(k, 0, n + 1) rep(i, 0, k + 1) t[k] += A[i][m] * B[k - i][m];
    rep(k, 0, n + 1) A[k][m] = t[k];
  }
  rep(k, 0, n + 1) tr(A[k], -1);
  vector<mint> c(N);
  rep(m, 0, N) c[m] = A[__builtin_popcount(m)][m];
  return c;
}
