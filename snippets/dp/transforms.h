/**
 * Name: Zeta and Möbius transforms
 * Description: Sums over a partial order, in place; `inv` undoes
 *   them (Möbius). Subsets: $g(m) = sum_(s subset.eq m) f(s)$,
 *   supersets likewise (size $2^B$). Divisors:
 *   $g(n) = sum_(d | n) f(d)$; multiples: $g(d) = sum_(d | n) f(n)$
 *   (indices $1..N$, entry $0$ unused). `xorT` is the Walsh–
 *   Hadamard transform. A convolution $c_k = sum_(i star j = k) a_i b_j$
 *   is: transform both, multiply pointwise, invert. $star$ = OR:
 *   subsets; AND: supersets; XOR: `xorT`; gcd: multiples; lcm:
 *   divisors (gives $c_k$ for $k <= N$).
 * Time: $O(2^B B)$; $O(N log log N)$
 */
#pragma once
using V = vector<ll>;
void subsets(V& f, bool inv = false) {
  int s = inv ? -1 : 1;
  for (int b = 1; b < sz(f); b *= 2)
    rep(m, 0, sz(f)) if (m & b) f[m] += s * f[m ^ b];
}
void supersets(V& f, bool inv = false) {
  int s = inv ? -1 : 1;
  for (int b = 1; b < sz(f); b *= 2)
    rep(m, 0, sz(f)) if (m & b) f[m ^ b] += s * f[m];
}
void xorT(V& f, bool inv = false) {
  for (int b = 1; b < sz(f); b *= 2)
    rep(m, 0, sz(f)) if (m & b) {
      ll u = f[m ^ b], v = f[m];
      f[m ^ b] = u + v, f[m] = u - v;
    }
  if (inv) for (ll& x : f) x /= sz(f);
}
vi& primes(int n) { // cached for the last n
  static int last = -1;
  static vi p;
  if (n == last) return p;
  last = n, p.clear();
  vector<bool> comp(n + 1);
  rep(i, 2, n + 1) if (!comp[i]) {
    p.push_back(i);
    for (ll j = (ll)i * i; j <= n; j += i) comp[j] = true;
  }
  return p;
}
void divisors(V& f, bool inv = false) {
  int N = sz(f) - 1;
  for (int p : primes(N))
    if (!inv)
      for (int i = 1; i <= N / p; ++i) f[i * p] += f[i];
    else
      for (int i = N / p; i >= 1; --i) f[i * p] -= f[i];
}
void multiples(V& f, bool inv = false) {
  int N = sz(f) - 1;
  for (int p : primes(N))
    if (!inv)
      for (int i = N / p; i >= 1; --i) f[i] += f[i * p];
    else
      for (int i = 1; i <= N / p; ++i) f[i] -= f[i * p];
}
// --- uses ---
// c = a (op) b, e.g. convolve(a, b, subsets) for OR.
V convolve(V a, V b, void (*T)(V&, bool)) {
  T(a, false), T(b, false);
  rep(i, 0, sz(a)) a[i] *= b[i];
  T(a, true);
  return a;
}
// Submasks s of m, decreasing (s = 0 handled separately):
//   for (int s = m; s; s = (s - 1) & m)
// Next mask with the same popcount (Gosper):
//   int c = x & -x, r = x + c;
//   x = (((r ^ x) >> 2) / c) | r;
// __builtin_popcountll, __builtin_ctzll (lowest set bit),
// 63 - __builtin_clzll(x) == __lg(x) (highest set bit).
