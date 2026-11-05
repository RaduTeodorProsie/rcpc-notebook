#include "number-theory/modint.h"
double abs(mint x) { return x.v; }
#include "number-theory/gauss.h"
#include "number-theory/det.h"
#include "testlib.h"
template <class T> T bruteDet(vector<vector<T>> a) {
  int n = sz(a);
  vi p(n);
  iota(all(p), 0);
  T r = 0;
  do {
    T t = 1;
    rep(i, 0, n) t = t * a[i][p[i]];
    int inv = 0;
    rep(i, 0, n) rep(j, i + 1, n) inv += p[i] > p[j];
    r = inv & 1 ? r - t : r + t;
  } while (next_permutation(all(p)));
  return r;
}
int main() {
  rep(it, 0, 2000) {
    int n = rnd(1, 6), m = rnd(1, 6);
    // solvable system, low-rank sometimes
    vector<vector<mint>> A(n, vector<mint>(m + 1));
    vector<mint> x0(m);
    for (auto& v : x0) v = rnd(0, 5);
    int rank = rnd(0, n);
    rep(i, 0, n) {
      if (i < rank || i == 0) rep(j, 0, m) A[i][j] = rnd(-3, 3);
      else { // combination of earlier rows
        rep(k, 0, i) { mint f = rnd(-2, 2); rep(j, 0, m) A[i][j] += f * A[k][j]; }
      }
      rep(j, 0, m) A[i][m] += A[i][j] * x0[j];
    }
    vector<mint> x;
    int r = gauss(A, x);
    CHECK(r >= 0);
    rep(i, 0, n) {
      mint s = 0;
      rep(j, 0, m) s += A[i][j] * x[j];
      CHECK(s == A[i][m]);
    }
    // make it inconsistent: duplicate a row with a different b
    auto B = A;
    B.push_back(A[0]);
    B.back()[m] += 1;
    CHECK(gauss(B, x) == -1);
    // rank equals rank of A without b
    auto Z = A;
    for (auto& row : Z) row[m] = 0;
    CHECK(gauss(Z, x) == r);
    // determinant
    int k = rnd(1, 6);
    vector<vector<mint>> D(k, vector<mint>(k));
    vector<vector<double>> Dd(k, vector<double>(k));
    rep(i, 0, k) rep(j, 0, k) Dd[i][j] = (D[i][j] = rnd(-4, 4)).v > 4 ? (double)D[i][j].v - MOD : D[i][j].v;
    CHECK(det(D) == bruteDet(D));
    CHECK(fabs(det(Dd) - bruteDet(Dd)) < 1e-6 * max(1.0, fabs(bruteDet(Dd))));
  }
  rep(it, 0, 500) {  // doubles, random square systems
    int n = rnd(1, 8);
    vector<vector<double>> A(n, vector<double>(n + 1));
    vector<double> x0(n), x;
    for (auto& v : x0) v = rndd(-5, 5);
    rep(i, 0, n) {
      rep(j, 0, n) A[i][j] = rndd(-5, 5);
      rep(j, 0, n) A[i][n] += A[i][j] * x0[j];
    }
    CHECK(gauss(A, x) == n);
    rep(j, 0, n) CHECK(fabs(x[j] - x0[j]) < 1e-6);
  }
}
