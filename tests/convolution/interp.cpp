#include "number-theory/modint.h"
#include "convolution/interp.h"
#include "testlib.h"
template <class T> T eval(const vector<T>& c, T x) {
  T r = 0;
  for (int i = sz(c); i--;) r = r * x + c[i];
  return r;
}
int main() {
  rep(it, 0, 2000) {  // mint: random polynomial, distinct points
    int n = rnd(1, 12);
    vector<mint> c(n);
    for (auto& v : c) v = rnd(0, MOD - 1);
    set<ll> used;
    vector<mint> x, y;
    while (sz(x) < n) {
      ll v = it % 2 ? rnd(0, 20) : rnd(0, MOD - 1);
      if (used.insert(v).second) x.push_back(v), y.push_back(eval(c, mint(v)));
    }
    vector<mint> r = interp(x, y);
    CHECK(sz(r) == n);
    rep(i, 0, n) CHECK(r[i] == c[i], "it=%d i=%d", it, i);
    // lagrange from p(0..n-1), at random t, including t < n
    vector<mint> ys(n);
    rep(i, 0, n) ys[i] = eval(c, mint(i));
    rep(k, 0, 5) {
      ll t = k < 2 ? rnd(0, n - 1) : rnd(0, MOD - 1);
      CHECK(lagrange(ys, mint(t)) == eval(c, mint(t)), "it=%d t=%lld", it, t);
    }
  }
  {  // sum of k-th powers: prefix sums of i^k are a degree k+1 polynomial
    rep(k, 0, 8) {
      vector<mint> ys(k + 2);
      mint s = 0;
      rep(i, 0, k + 2) ys[i] = s, s += mint(i).pow(k);
      ll N = 1000;  // sum_{i < N} i^k
      mint want = 0;
      rep(i, 0, N) want += mint(i).pow(k);
      CHECK(lagrange(ys, mint(N)) == want);
    }
  }
  rep(it, 0, 500) {  // doubles, small n
    int n = rnd(1, 8);
    vector<double> c(n), x, y;
    for (auto& v : c) v = rndd(-3, 3);
    set<ll> used;
    while (sz(x) < n) {
      ll v = rnd(-10, 10);
      if (used.insert(v).second) x.push_back(v), y.push_back(eval(c, (double)v));
    }
    vector<double> r = interp(x, y);
    rep(i, 0, n) CHECK(fabs(r[i] - c[i]) < 1e-6, "it=%d i=%d %f %f", it, i, r[i], c[i]);
    vector<double> ys(n);
    rep(i, 0, n) ys[i] = eval(c, (double)i);
    double t = rndd(-5, 15);
    CHECK(fabs(lagrange(ys, t) - eval(c, t)) < 1e-6 * max(1.0, fabs(eval(c, t))));
  }
}
