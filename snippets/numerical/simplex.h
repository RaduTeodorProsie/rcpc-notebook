/**
 * Name: Simplex
 * Description: Maximizes $c^T x$ subject to $A x <= b$, $x >= 0$:
 *   returns the maximum and sets `x`, or `-LP::inf` if infeasible,
 *   `LP::inf` if unbounded. $>=$: negate the row; $=$: both; a free
 *   variable is $x' - x''$; minimize: negate $c$. Dual:
 *   max ${c^T x | A x <= b, x >= 0} =$
 *   min ${b^T y | A^T y >= c, y >= 0}$ if either is finite.
 * Usage: double v = LP(A, b, c).solve(x); // A: vector<vd>
 * Time: $O(n m)$ per pivot, fast in practice
 */
#pragma once
using vd = vector<double>;
struct LP {
  static constexpr double eps = 1e-8, inf = HUGE_VAL;
  int m, n; vi B, N; vector<vd> D;
  LP(const vector<vd>& A, const vd& b, const vd& c)
      : m(sz(b)), n(sz(c)), B(m), N(n + 1),
        D(m + 2, vd(n + 2)) {
    rep(i, 0, m) rep(j, 0, n) D[i][j] = A[i][j];
    rep(i, 0, m) B[i] = n + i, D[i][n] = -1;
    rep(i, 0, m) D[i][n + 1] = b[i];
    rep(j, 0, n) N[j] = j, D[m][j] = -c[j];
    N[n] = -1, D[m + 1][n] = 1;
  }
  void pivot(int r, int s) { // swap basic B[r], free N[s]
    double inv = 1 / D[r][s];
    rep(i, 0, m + 2) if (i != r && abs(D[i][s]) > eps) {
      double k = D[i][s] * inv;
      rep(j, 0, n + 2) D[i][j] -= D[r][j] * k;
      D[i][s] = D[r][s] * k;
    }
    rep(j, 0, n + 2) if (j != s) D[r][j] *= inv;
    rep(i, 0, m + 2) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }
  bool lt(const vd& v, int j, int s) { // v[j] < v[s], ties
    return s < 0 || pair(v[j], N[j]) < pair(v[s], N[s]);
  }
  bool simplex(int phase) {
    int x = m + phase - 1;
    while (1) {
      int s = -1, r = -1; // entering: most negative
      rep(j, 0, n + 1)
        if (N[j] != -phase && lt(D[x], j, s)) s = j;
      if (D[x][s] >= -eps) return true;
      rep(i, 0, m) if (D[i][s] > eps) { // leaving: tightest
        pair a(D[i][n + 1] / D[i][s], B[i]);
        if (r < 0 || a < pair(D[r][n + 1] / D[r][s], B[r]))
          r = i;
      }
      if (r < 0) return false;
      pivot(r, s);
    }
  }
  double solve(vd& x) {
    int r = 0;
    rep(i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (m && D[r][n + 1] < -eps) { // phase 1
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps)
        return -inf;
      rep(i, 0, m) if (B[i] == -1) {
        int s = 0;
        rep(j, 1, n + 1) if (lt(D[i], j, s)) s = j;
        pivot(i, s);
      }
    }
    bool ok = simplex(1);
    x = vd(n);
    rep(i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};
