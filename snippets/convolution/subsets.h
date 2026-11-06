/**
 * Name: Subset zeta and Möbius
 * Description: For an array over bitmasks (size $2^B$), the zeta
 *   transform replaces $f(m)$ by $sum_(s subset.eq m) f(s)$, the sum
 *   over all submasks. Möbius (`inv`) is its inverse: from those
 *   sums it gives $f$ back. One bit at a time: after bit $b$,
 *   $f(m)$ is the sum over the $s$ obtained from $m$ by clearing
 *   some of bits $0..b$. OR convolution
 *   $c_k = sum_(i | j = k) a_i b_j$: zeta both, multiply pointwise,
 *   Möbius; it works because $i | j subset.eq m$ iff both $i, j subset.eq m$.
 * Usage: subsets(a), subsets(b);
 *   rep(i, 0, sz(a)) a[i] *= b[i];
 *   subsets(a, true); // a = OR convolution
 * Time: $O(2^B B)$
 */
#pragma once
void subsets(vector<ll>& f, bool inv = false) {
  ll s = inv ? -1 : 1;
  for (int b = 1; b < sz(f); b *= 2)
    for (int i = 0; i < sz(f); i += 2 * b)
      rep(m, i, i + b) f[m + b] += s * f[m];
}
// --- uses ---
// Submasks s of m, decreasing (s = 0 handled separately):
//   for (int s = m; s; s = (s - 1) & m)
// All (m, submask) pairs this way: O(3^B).
// Next mask with the same popcount (Gosper):
//   int c = x & -x, r = x + c;
//   x = (((r ^ x) >> 2) / c) | r;
// __builtin_popcountll, __builtin_ctzll (lowest set bit),
// 63 - __builtin_clzll(x) == __lg(x) (highest set bit).
