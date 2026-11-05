/**
 * Name: Subset sums and bit tricks
 * Description: `sos` turns $f$ into $g(m) = sum_(s subset.eq m) f(s)$;
 *   `unsos` inverts it. For sums over supersets, test
 *   `!(m >> b & 1)` and use `m | 1 << b`. Uses: bit tricks.
 * Time: $O(2^B B)$
 */
#pragma once
void sos(vector<ll>& f, int B) {
  rep(b, 0, B) rep(m, 0, 1 << B) if (m >> b & 1)
    f[m] += f[m ^ 1 << b];
}
void unsos(vector<ll>& f, int B) {
  rep(b, 0, B) rep(m, 0, 1 << B) if (m >> b & 1)
    f[m] -= f[m ^ 1 << b];
}
// --- uses ---
// All submasks s of m, decreasing (add s = 0 separately):
//   for (int s = m; s; s = (s - 1) & m)
// Next mask with the same popcount (Gosper):
//   int c = x & -x, r = x + c;
//   x = (((r ^ x) >> 2) / c) | r;
// __builtin_popcountll, __builtin_ctzll (lowest set bit),
// 63 - __builtin_clzll(x) == __lg(x) (highest set bit).
