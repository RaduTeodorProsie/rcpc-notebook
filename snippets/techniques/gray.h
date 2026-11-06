/**
 * Name: Gray codes
 * Description: Orders where each step changes little.
 *   `gray(i)`, $i = 0..2^n - 1$: all $n$-bit masks; step
 *   $i -> i + 1$ flips bit `ctz(i + 1)`, last to first flips bit
 *   $n - 1$. `igray` inverts it; from mask $x$: `x ^ gray(i)`.
 *   `kgray(m, n, k)`: $m$-th word of $n$ digits in $0..k-1$
 *   (digit 0 first); a step moves one digit by $plus.minus 1$.
 *   `combs(n, k)`: $k$-subsets of $0..n-1$ as masks; a step
 *   swaps one element out and one in, cyclically.
 *   `sjt(n)`: all permutations; a step swaps two neighbours.
 * Time: lists $O(n)$ per item
 */
#pragma once
ll gray(ll i) { return i ^ i >> 1; }
ll igray(ll g) {
  for (ll s = g; s >>= 1;) g ^= s;
  return g;
}
vi kgray(ll m, int n, int k) {
  vi g(n);
  rep(i, 0, n) g[i] = int(m % k), m /= k;
  for (int i = n, f = 0; i--; f ^= g[i] & 1)
    if (f) g[i] = k - 1 - g[i];
  return g;
}
vector<ll> combs(int n, int k) {
  if (k == 0 || k == n) return {(1LL << k) - 1};
  auto a = combs(n - 1, k), b = combs(n - 1, k - 1);
  for (int i = sz(b); i--;)
    a.push_back(b[i] | 1LL << (n - 1));
  return a;
}
vector<vi> sjt(int n) {
  if (!n) return {{}};
  vector<vi> r, s = sjt(n - 1);
  rep(i, 0, sz(s)) rep(j, 0, n) { // n - 1 sweeps across
    vi p = s[i];
    p.insert(p.begin() + (i % 2 ? j : n - 1 - j), n - 1);
    r.push_back(p);
  }
  return r;
}
