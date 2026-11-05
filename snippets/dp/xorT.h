/**
 * Name: Walsh–Hadamard transform
 * Description: Replaces $f(m)$ by $sum_s (-1)^(|s \& m|) f(s)$, where
 *   $|s \& m|$ is the number of common bits. Its inverse is the same
 *   transform divided by $2^B$ (`inv`; modulo a prime, multiply by
 *   the inverse of $2^B$ instead). XOR convolution
 *   $c_k = sum_(i xor j = k) a_i b_j$: transform both, multiply
 *   pointwise, invert.
 * Usage: xorT(a), xorT(b);
 *   rep(i, 0, sz(a)) a[i] *= b[i];
 *   xorT(a, true); // a = XOR convolution
 * Time: $O(2^B B)$
 */
#pragma once
void xorT(vector<ll>& f, bool inv = false) {
  for (int b = 1; b < sz(f); b *= 2)
    for (int i = 0; i < sz(f); i += 2 * b)
      rep(m, i, i + b) {
        ll u = f[m], v = f[m + b];
        f[m] = u + v, f[m + b] = u - v;
      }
  if (inv) for (ll& x : f) x /= sz(f);
}
