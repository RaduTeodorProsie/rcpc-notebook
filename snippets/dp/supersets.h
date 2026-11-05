/**
 * Name: Superset zeta and Möbius
 * Description: Replaces $f(m)$ by $sum_(s supset.eq m) f(s)$, the sum
 *   over all supermasks; `inv` undoes it. AND convolution
 *   $c_k = sum_(i \& j = k) a_i b_j$: zeta both, multiply pointwise,
 *   Möbius ($i \& j supset.eq m$ iff both $i, j supset.eq m$).
 *   Typical: $g(m)$ = how many items contain all bits of $m$.
 * Usage: supersets(a), supersets(b);
 *   rep(i, 0, sz(a)) a[i] *= b[i];
 *   supersets(a, true); // a = AND convolution
 * Time: $O(2^B B)$
 */
#pragma once
void supersets(vector<ll>& f, bool inv = false) {
  ll s = inv ? -1 : 1;
  for (int b = 1; b < sz(f); b *= 2)
    for (int i = 0; i < sz(f); i += 2 * b)
      rep(m, i, i + b) f[m] += s * f[m + b];
}
