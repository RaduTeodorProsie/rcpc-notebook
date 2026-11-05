/**
 * Name: Determinant
 * Description: Same conventions as Gaussian elimination:
 *   `double`, or `mint` together with `abs(mint)`.
 * Time: $O(n^3)$
 */
#pragma once
template <class T> T det(vector<vector<T>> a) {
  int n = sz(a);
  T d = 1;
  rep(c, 0, n) {
    int p = c;
    rep(i, c, n) if (abs(a[i][c]) > abs(a[p][c])) p = i;
    if (abs(a[p][c]) < 1e-9) return 0;
    if (p != c) swap(a[p], a[c]), d = T(0) - d;
    d = d * a[c][c];
    T iv = T(1) / a[c][c];
    rep(i, c + 1, n) {
      T f = a[i][c] * iv;
      rep(j, c, n) a[i][j] = a[i][j] - f * a[c][j];
    }
  }
  return d;
}
