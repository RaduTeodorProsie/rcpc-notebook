/**
 * Name: Gaussian elimination
 * Description: Solves $A x = b$; `a` is $n times (m+1)$ with $b$ as
 *   the last column. Returns the rank and one solution in `x`
 *   (free variables $0$), or $-1$ if there is none; with $b = 0$
 *   the result is the rank of $A$. Written for `double`; for a
 *   prime modulus pass `mint` matrices and also define
 *   `double abs(mint x) { return x.v; }`.
 * Time: $O(n m min(n, m))$
 */
#pragma once
template <class T>
int gauss(vector<vector<T>> a, vector<T>& x) {
  int n = sz(a), m = sz(a[0]) - 1, r = 0;
  vi where(m, -1);
  for (int c = 0; c < m && r < n; ++c) {
    int p = r;
    rep(i, r, n) if (abs(a[i][c]) > abs(a[p][c])) p = i;
    if (abs(a[p][c]) < 1e-9) continue;
    swap(a[p], a[r]);
    T iv = T(1) / a[r][c];
    for (T& v : a[r]) v = v * iv;
    rep(i, 0, n) if (i != r) {
      T f = a[i][c];
      rep(j, c, m + 1) a[i][j] = a[i][j] - f * a[r][j];
    }
    where[c] = r++;
  }
  rep(i, r, n) if (abs(a[i][m]) > 1e-9) return -1;
  x.assign(m, T(0));
  rep(c, 0, m) if (where[c] >= 0) x[c] = a[where[c]][m];
  return r;
}
