// Performance: segment tree beats and simplex, whose running times have no
// short proof (amortized potential arguments / exponential worst case).
#include "data-structures/beats.h"
#include "numerical/simplex.h"
#include "testlib.h"
int main() {
  const int n = 200000, q = 200000;
  ll check = 0;
  PERF("beats: random chmin/chmax/add/query 2e5", 400) {
    Beats b(rvec(n, -1e9, 1e9));
    rep(i, 0, q) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n), t = rnd(0, 3);
      if (t == 0) b.chmin(l, r, rnd(-1e9, 1e9));
      else if (t == 1) b.chmax(l, r, rnd(-1e9, 1e9));
      else if (t == 2) b.add(l, r, rnd(-1e9, 1e9));
      else check += b.query(l, r)[0];
    }
  }
  // Distinct values; adds on random prefixes keep re-splitting them, and
  // whole-array chmin/chmax keep merging them: the O(log^2) case.
  PERF("beats: add on prefixes + global chmin/chmax", 300) {
    vector<ll> a(n);
    rep(i, 0, n) a[i] = i;
    Beats b(a);
    rep(i, 0, q) {
      b.add(0, rnd(1, n), rnd(1, n));
      auto [s, mx, mn] = b.query(0, n);
      ll mid = mn + (mx - mn) / 2;
      if (i % 2) b.chmin(0, n, mid + rnd(0, (mx - mn) / 4));
      else b.chmax(0, n, mid - rnd(0, (mx - mn) / 4));
      check += s;
    }
  }
  PERF("beats: chmin with decreasing values, whole range", 200) {
    Beats b(rvec(n, 0, 1e9));
    for (ll v = 1e9; v > 0; v -= 5000) b.chmin(0, n, v), check += b.query(0, n)[0];
  }
  auto randomLP = [](int m, int k, bool negB) {
    // feasible by construction (b = A x0 + slack, x0 >= 0) and bounded
    // (every variable has a positive coefficient in a row with A >= 0)
    vector<vd> A(m, vd(k));
    vd b(m), c(k), x0(k);
    rep(i, 0, m) rep(j, 0, k) A[i][j] = negB ? rnd(-5, 10) : rnd(0, 10);
    rep(j, 0, k) A[0][j] = rnd(1, 10);
    for (auto& v : x0) v = rnd(0, 10);
    rep(i, 0, m) {
      double s = 0;
      rep(j, 0, k) s += A[i][j] * x0[j];
      b[i] = s + rnd(0, 100);
    }
    for (auto& v : c) v = rnd(1, 10);
    return tuple{A, b, c};
  };
  double obj = 0;
  PERF("simplex: random 400 x 400, b >= 0", 400) {
    auto [A, b, c] = randomLP(400, 400, false);
    vd x;
    double v = LP(A, b, c).solve(x);
    CHECK(fabs(v) < LP::inf, "%f", v);
    obj += v;
  }
  PERF("simplex: random 300 x 300, negative b (phase 1)", 400) {
    auto [A, b, c] = randomLP(300, 300, true);
    rep(i, 1, sz(b)) b[i] -= 50;  // many rows violated at x = 0
    vd x;
    double v = LP(A, b, c).solve(x);
    CHECK(fabs(v) < LP::inf, "%f", v);
    obj += v;
  }
  // Klee-Minty cube: the most-negative pivot rule visits all 2^n vertices.
  PERF("simplex: Klee-Minty n = 16 (65535 pivots)", 200) {
    int k = 16;
    vector<vd> A(k, vd(k));
    vd b(k), c(k), x;
    rep(i, 0, k) {
      rep(j, 0, i) A[i][j] = pow(2, i - j + 1);
      A[i][i] = 1, b[i] = pow(5, i + 1), c[i] = pow(2, k - 1 - i);
    }
    double v = LP(A, b, c).solve(x);
    CHECK(fabs(v - pow(5, k)) < 1e-6 * pow(5, k), "%f", v);
  }
  printf("checksum %lld %.3f\n", check, obj);
}
