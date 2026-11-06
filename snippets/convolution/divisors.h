/**
 * Name: Divisor zeta and Möbius
 * Description: Indices $1..N$ (entry $0$ unused). Replaces $f(n)$
 *   by $sum_(d | n) f(d)$; `inv` undoes it, which is Möbius
 *   inversion: $f(n) = sum_(d | n) mu(n\/d) g(d)$. LCM convolution
 *   $c_k = sum_(op("lcm")(i,j) = k) a_i b_j$ for $k <= N$: zeta both,
 *   multiply pointwise, Möbius ($op("lcm")(i, j) | n$ iff $i | n$ and $j | n$).
 * Usage: divisors(a), divisors(b);
 *   rep(i, 1, sz(a)) a[i] *= b[i];
 *   divisors(a, true); // a = LCM convolution
 * Time: $O(N log N)$
 */
#pragma once
void divisors(vector<ll>& f, bool inv = false) {
  int N = sz(f) - 1;
  for (int i = 1; i <= N; ++i) {
    int d = inv ? i : N + 1 - i; // f[d] is original
    for (int m = 2 * d; m <= N; m += d)
      f[m] += inv ? -f[d] : f[d];
  }
}
