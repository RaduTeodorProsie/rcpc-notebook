/**
 * Name: Polynomial interpolation
 * Description: `interp(x, y)`: coefficients (lowest degree first)
 *   of the unique polynomial of degree $< n$ through the points
 *   $(x_i, y_i)$, $x_i$ distinct. `lagrange(y, t)`: $p(t)$ for the
 *   polynomial of degree $< n$ with $p(i) = y_i$, $i = 0..n-1$
 *   (sums of $k$-th powers: $n = k + 2$ prefix sums). `T` is
 *   `mint` or `double` (doubles lose precision fast for $n > 20$).
 * Time: `interp` $O(n^2)$, `lagrange` $O(n)$ divisions
 */
#pragma once
template <class T>
vector<T> interp(vector<T> x, vector<T> y) {
  int n = sz(x);
  vector<T> r(n), b(n); // b: prod of (X - x_j), j < k
  rep(k, 0, n - 1) rep(i, k + 1, n) // Newton differences
    y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  b[0] = 1;
  rep(k, 0, n) {
    T last = 0;
    rep(i, 0, n) {
      r[i] += y[k] * b[i];
      T cur = b[i];
      b[i] = last - cur * x[k];
      last = cur;
    }
  }
  return r;
}
template <class T> T lagrange(const vector<T>& y, T t) {
  int n = sz(y);
  vector<T> pre(n + 1, 1), suf(n + 1, 1), f(n, 1);
  rep(i, 0, n) pre[i + 1] = pre[i] * (t - T(i));
  for (int i = n; i--;) suf[i] = suf[i + 1] * (t - T(i));
  rep(i, 1, n) f[i] = f[i - 1] * T(i);
  T r = 0;
  rep(i, 0, n) {
    T a = y[i] * pre[i] * suf[i + 1] /
          (f[i] * f[n - 1 - i]);
    r += (n - 1 - i) % 2 ? -a : a;
  }
  return r;
}
