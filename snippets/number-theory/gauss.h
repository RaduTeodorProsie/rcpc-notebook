/**
 * Name: Gaussian elimination
 * Description: Solves $A x = b$ over `double` or `mint`; `a` is
 *   $n times (m+1)$ with $b$ as the last column. Returns the rank
 *   and one solution in `x` (free variables $0$), or $-1$ if
 *   there is none. Uses: determinant.
 * Time: $O(n m min(n, m))$
 */
#pragma once
#include "modint.h"
const double EPS = 1e-9;
double mag(double v) { return fabs(v); }
double mag(mint v) { return v.v != 0; }
template <class T>
int gauss(vector<vector<T>> a, vector<T>& x) {
  int n = sz(a), m = sz(a[0]) - 1, r = 0;
  vi where(m, -1);
  for (int c = 0; c < m && r < n; ++c) {
    int p = r;
    rep(i, r, n) if (mag(a[i][c]) > mag(a[p][c])) p = i;
    if (mag(a[p][c]) < EPS) continue;
    swap(a[p], a[r]);
    T iv = T(1) / a[r][c];
    for (T& v : a[r]) v = v * iv;
    rep(i, 0, n) if (i != r) {
      T f = a[i][c];
      rep(j, c, m + 1) a[i][j] = a[i][j] - f * a[r][j];
    }
    where[c] = r++;
  }
  rep(i, r, n) if (mag(a[i][m]) > EPS) return -1;
  x.assign(m, T(0));
  rep(c, 0, m) if (where[c] >= 0) x[c] = a[where[c]][m];
  return r;
}
// --- uses ---
template <class T> T det(vector<vector<T>> a) {
  int n = sz(a);
  T d = 1;
  rep(c, 0, n) {
    int p = c;
    rep(i, c, n) if (mag(a[i][c]) > mag(a[p][c])) p = i;
    if (mag(a[p][c]) < EPS) return 0;
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
