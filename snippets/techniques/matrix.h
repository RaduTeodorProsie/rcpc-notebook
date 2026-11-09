/**
 * Name: Matrix power
 * Description: `mpow(A, e)` is $A^e$ modulo `MOD` (drop its line if
 *   `modint.h` is in); entries must be
 *   reduced mod `MOD` (write $-c$ as `MOD` $- c$). Linear recurrence
 *   $a_n = c_1 a_(n-1) + dots + c_k a_(n-k)$: the state
 *   $(a_(n-1), dots, a_(n-k))$ times the companion matrix (first row
 *   $c_1..c_k$, then $1$s just below the diagonal) gives the next
 *   state. Add a constant: one more state component fixed at $1$.
 *   Prefix sums: one more component $s_n = s_(n-1) + a_n$. Walks:
 *   $(A^k)_(u v)$ counts walks of length $k$ from $u$ to $v$. With
 *   $(min, +)$ in place of $(+, dot)$ in `mul`: shortest walk with
 *   exactly $k$ edges.
 * Usage: Mat T = {{1, 1}, {1, 0}}; // Fibonacci
 *   ll f = mpow(T, n)[0][1]; // F_n
 * Time: $O(k^3 log e)$
 */
#pragma once
using Mat = vector<vector<ll>>;
const ll MOD = 1000000007; //!
Mat mul(const Mat& a, const Mat& b) {
  int n = sz(a), k = sz(b), m = sz(b[0]);
  Mat c(n, vector<ll>(m));
  rep(i, 0, n) rep(l, 0, k) if (a[i][l]) rep(j, 0, m)
    c[i][j] = (c[i][j] + a[i][l] * b[l][j]) % MOD;
  return c;
}
Mat mpow(Mat a, ll e) {
  Mat r(sz(a), vector<ll>(sz(a)));
  rep(i, 0, sz(a)) r[i][i] = 1;
  for (; e; e >>= 1, a = mul(a, a))
    if (e & 1) r = mul(r, a);
  return r;
}
