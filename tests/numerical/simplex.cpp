#include "numerical/simplex.h"
#include "testlib.h"
// Brute force: the optimum of a bounded LP is at a vertex, where n of the constraints
// (rows of A, or x_j >= 0, or the box x_j <= BOX) are tight. Try every choice.
pair<bool, double> brute(const vector<vd>& A, const vd& b, const vd& c, double BOX) {
  int m = sz(A), n = sz(c);
  vector<vd> rows;
  vd rhs;
  rep(i, 0, m) rows.push_back(A[i]), rhs.push_back(b[i]);
  rep(j, 0, n) {
    vd r(n);
    r[j] = -1, rows.push_back(r), rhs.push_back(0);
    r[j] = 1, rows.push_back(r), rhs.push_back(BOX);
  }
  int R = sz(rows);
  bool found = false;
  double best = -1e300;
  vi pick;
  auto rec = [&](auto& self, int from) -> void {
    if (sz(pick) == n) {  // solve rows[pick] x = rhs[pick]
      vector<vd> M(n, vd(n + 1));
      rep(i, 0, n) {
        rep(j, 0, n) M[i][j] = rows[pick[i]][j];
        M[i][n] = rhs[pick[i]];
      }
      rep(col, 0, n) {
        int p = col;
        rep(i, col, n) if (fabs(M[i][col]) > fabs(M[p][col])) p = i;
        if (fabs(M[p][col]) < 1e-9) return;
        swap(M[p], M[col]);
        rep(i, 0, n) if (i != col) {
          double k = M[i][col] / M[col][col];
          rep(j, 0, n + 1) M[i][j] -= k * M[col][j];
        }
      }
      vd x(n);
      rep(i, 0, n) x[i] = M[i][n] / M[i][i];
      rep(i, 0, R) {
        double s = 0;
        rep(j, 0, n) s += rows[i][j] * x[j];
        if (s > rhs[i] + 1e-6) return;
      }
      double v = 0;
      rep(j, 0, n) v += c[j] * x[j];
      found = true, best = max(best, v);
      return;
    }
    rep(i, from, R) pick.push_back(i), self(self, i + 1), pick.pop_back();
  };
  rec(rec, 0);
  return {found, best};
}
int main() {
  {  // the usage example: min x + y with x + 2y >= 4, |x - y| <= 1
    vector<vd> A{{1, -1}, {-1, 1}, {-1, -2}};
    vd b{1, 1, -4}, c{-1, -1}, x;
    double val = LP(A, b, c).solve(x);
    CHECK(fabs(val + 7.0 / 3) < 1e-9 && fabs(x[0] - 2.0 / 3) < 1e-9 && fabs(x[1] - 5.0 / 3) < 1e-9);
  }
  int counts[3] = {};
  rep(it, 0, 20000) {
    int n = rnd(1, 3), m = rnd(0, 4);
    vector<vd> A(m, vd(n));
    vd b(m), c(n);
    for (auto& r : A) for (auto& v : r) v = rnd(-3, 3);
    for (auto& v : b) v = rnd(-4, 6);
    for (auto& v : c) v = rnd(-3, 3);
    vd x;
    double val = LP(A, b, c).solve(x);
    auto [feas, small] = brute(A, b, c, 1e3);
    auto [feas2, large] = brute(A, b, c, 1e6);
    CHECK(feas == feas2);
    if (!feas) {
      CHECK(val == -LP::inf, "it=%d got %f", it, val);
      ++counts[0];
      continue;
    }
    // with only small integer data, a bounded optimum does not depend on the box
    bool unbounded = large > small + 1;
    if (unbounded) {
      CHECK(val == LP::inf, "it=%d got %f, brute %f %f", it, val, small, large);
      ++counts[1];
      continue;
    }
    CHECK(fabs(val - small) < 1e-6, "it=%d got %f want %f", it, val, small);
    CHECK(sz(x) == n);
    double v = 0;
    rep(j, 0, n) {
      CHECK(x[j] >= -1e-9);
      v += c[j] * x[j];
    }
    CHECK(fabs(v - val) < 1e-6);
    rep(i, 0, m) {
      double s = 0;
      rep(j, 0, n) s += A[i][j] * x[j];
      CHECK(s <= b[i] + 1e-6);
    }
    ++counts[2];
  }
  CHECK(counts[0] > 500 && counts[1] > 500 && counts[2] > 500, "%d %d %d", counts[0], counts[1], counts[2]);
  {  // duality on random bounded LPs: max c x (Ax<=b, x>=0) = min b y (A^T y >= c, y>=0)
    rep(it, 0, 2000) {
      int n = rnd(1, 5), m = rnd(1, 5);
      vector<vd> A(m, vd(n));
      vd b(m), c(n), x, y;
      for (auto& r : A) for (auto& v : r) v = rnd(0, 5);
      for (auto& v : b) v = rnd(1, 10);
      for (auto& v : c) v = rnd(-3, 5);
      rep(j, 0, n) A[rnd(0, m - 1)][j] = rnd(1, 5);  // every variable is bounded
      double p = LP(A, b, c).solve(x);
      vector<vd> At(n, vd(m));
      vd nb(m), nc(n);
      rep(i, 0, m) rep(j, 0, n) At[j][i] = -A[i][j];
      rep(i, 0, m) nb[i] = -b[i];
      rep(j, 0, n) nc[j] = -c[j];
      double d = -LP(At, nc, nb).solve(y);
      CHECK(fabs(p - d) < 1e-6, "it=%d primal %f dual %f", it, p, d);
    }
  }
  {  // a bigger LP: a random flow-like problem, checked by feasibility and duality
    int n = 60, m = 80;
    vector<vd> A(m, vd(n));
    vd b(m), c(n), x, y;
    for (auto& r : A) for (auto& v : r) v = rnd(0, 1) ? rndd(0, 1) : 0;
    for (auto& v : b) v = rndd(1, 2);
    for (auto& v : c) v = rndd(0, 1);
    rep(j, 0, n) A[rnd(0, m - 1)][j] += 1;
    double p = LP(A, b, c).solve(x);
    vector<vd> At(n, vd(m));
    vd nb(m), nc(n);
    rep(i, 0, m) rep(j, 0, n) At[j][i] = -A[i][j];
    rep(i, 0, m) nb[i] = -b[i];
    rep(j, 0, n) nc[j] = -c[j];
    double d = -LP(At, nc, nb).solve(y);
    CHECK(fabs(p - d) < 1e-6 && p > 0, "%f %f", p, d);
  }
}
