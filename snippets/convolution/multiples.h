/**
 * Name: Multiple zeta and Möbius
 * Description: Indices $1..N$ (entry $0$ unused). Replaces $f(d)$
 *   by $sum_(d | n <= N) f(n)$; `inv` undoes it:
 *   $f(d) = sum_(d | n) mu(n\/d) g(n)$. GCD convolution
 *   $c_k = sum_(gcd(i,j) = k) a_i b_j$: zeta both, multiply
 *   pointwise, Möbius ($d | gcd(i, j)$ iff $d | i$ and $d | j$).
 *   Typical: pairs with gcd exactly $k$, from the easy count of
 *   pairs that are both multiples of $d$.
 * Usage: multiples(a), multiples(b);
 *   rep(i, 1, sz(a)) a[i] *= b[i];
 *   multiples(a, true); // a = GCD convolution
 * Time: $O(N log N)$
 */
#pragma once
void multiples(vector<ll>& f, bool inv = false) {
  int N = sz(f) - 1;
  for (int i = 1; i <= N; ++i) {
    int d = inv ? N + 1 - i : i; // f[m] is original
    for (int m = 2 * d; m <= N; m += d)
      f[d] += inv ? -f[m] : f[m];
  }
}
