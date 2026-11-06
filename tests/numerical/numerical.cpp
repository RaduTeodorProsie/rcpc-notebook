#include "numerical/ternary.h"
#include "numerical/simpson.h"
#include "numerical/fracsearch.h"
#include "testlib.h"
bool near(double a, double b, double e) { return fabs(a - b) <= e * max(1.0, fabs(b)); }
// p/q < u/v for q, v >= 0 (1/0 is +infinity)
bool less_(Fr a, Fr b) { return (__int128)a.p * b.q < (__int128)b.p * a.q; }
int main() {
  {  // integer ternary search vs brute force on random unimodal arrays
    rep(it, 0, 20000) {
      int n = rnd(1, 30), peak = rnd(0, n - 1), flat = rnd(0, n - 1 - peak);
      vector<ll> v(n);
      v[peak] = rnd(-5, 5);
      for (int i = peak - 1; i >= 0; --i) v[i] = v[i + 1] - rnd(1, 3);
      rep(i, peak + 1, n) v[i] = i <= peak + flat ? v[peak] : v[i - 1] - rnd(0, 2);
      ll lo = rnd(-1e12, 1e12), calls = 0;
      ll x = ternInt(lo, lo + n - 1, [&](ll t) { ++calls; return v[t - lo]; });
      CHECK(x - lo == peak, "n=%d got %lld want %d", n, x - lo, peak);
      CHECK(calls <= 2 * (__lg(max(n, 1)) + 2));
    }
    // huge range: f(x) = -(x - c)^2 as __int128
    rep(it, 0, 1000) {
      ll c = rnd(-1e18, 1e18);
      ll x = ternInt(LLONG_MIN / 2, LLONG_MAX / 2, [&](ll t) { return -((__int128)(t - c) * (t - c)); });
      CHECK(x == c);
    }
  }
  {  // golden section on several unimodal functions
    rep(it, 0, 3000) {
      double c = rndd(-100, 100), a = c - rndd(0.1, 1000), b = c + rndd(0.1, 1000), s = rndd(0.1, 10);
      int calls = 0;
      auto quad = [&](double x) { ++calls; return -s * (x - c) * (x - c) + 7; };
      CHECK(fabs(golden(a, b, quad) - c) < 1e-6 * max(1.0, b - a), "c=%f", c);
      CHECK(calls == 102);
      CHECK(fabs(golden(a, b, [&](double x) { return -fabs(x - c); }) - c) < 1e-6 * max(1.0, b - a));
      double m = golden(a, b, [&](double x) { return -cosh((x - c) / 50); });
      CHECK(fabs(m - c) < 1e-3, "%f %f", m, c);
    }
    // maximum at an end of the interval
    CHECK(fabs(golden(0, 10, [](double x) { return x; }) - 10) < 1e-9);
    CHECK(fabs(golden(0, 10, [](double x) { return -x; }) - 0) < 1e-9);
  }
  {  // integration
    rep(it, 0, 2000) {  // cubics are exact for Simpson
      double c0 = rndd(-5, 5), c1 = rndd(-5, 5), c2 = rndd(-5, 5), c3 = rndd(-5, 5);
      double a = rndd(-10, 10), b = a + rndd(0, 10);
      auto F = [&](double x) { return c0 * x + c1 * x * x / 2 + c2 * x * x * x / 3 + c3 * x * x * x * x / 4; };
      double got = integrate(a, b, [&](double x) { return c0 + c1 * x + c2 * x * x + c3 * x * x * x; });
      CHECK(fabs(got - (F(b) - F(a))) < 1e-7 * max(1.0, fabs(F(b)) + fabs(F(a))));
    }
    CHECK(near(integrate(0, M_PI, [](double x) { return sin(x); }), 2, 1e-9));
    CHECK(near(integrate(-1, 1, [](double x) { return sqrt(max(0.0, 1 - x * x)); }), M_PI / 2, 1e-7));
    CHECK(near(integrate(0, 5, [](double x) { return exp(x); }), exp(5) - 1, 1e-9));
    CHECK(near(integrate(2, 2, [](double x) { return x; }), 0, 1e-12));
    CHECK(near(integrate(3, 1, [](double x) { return x; }), -4, 1e-9));
    rep(it, 0, 300) {  // narrow peak somewhere in a wide interval
      double mu = rndd(0, 10), s = rndd(0.05, 0.5);
      double got = integrate(-10, 20, [&](double x) { return exp(-(x - mu) * (x - mu) / (2 * s * s)); });
      CHECK(near(got, s * sqrt(2 * M_PI), 1e-6), "mu=%f s=%f got %f", mu, s, got);
    }
    // piecewise: |x - c| split at the kink is exact, unsplit is still close
    rep(it, 0, 300) {
      double c = rndd(-1, 1), want = ((c + 1) * (c + 1) + (1 - c) * (1 - c)) / 2;
      auto f = [&](double x) { return fabs(x - c); };
      CHECK(near(integrate(-1, c, f) + integrate(c, 1, f), want, 1e-12));
      CHECK(near(integrate(-1, 1, f), want, 1e-6));
    }
    double disk = integrate2(-1, 1, [](double x) { return -sqrt(max(0.0, 1 - x * x)); },
                             [](double x) { return sqrt(max(0.0, 1 - x * x)); }, [](double, double) { return 1.0; });
    CHECK(near(disk, M_PI, 1e-6), "%f", disk);
    double xy = integrate2(0, 2, [](double) { return 0.0; }, [](double) { return 3.0; },
                           [](double x, double y) { return x * y * y; });
    CHECK(near(xy, 2 * 9, 1e-9));
  }
  {  // fraction search vs all fractions with p, q <= N
    rep(it, 0, 3000) {
      ll N = rnd(1, 25), u = rnd(0, 40), v = rnd(1, 40);
      bool strict = rnd(0, 1);  // f: p/q > u/v  or  p/q >= u/v
      auto f = [&](Fr x) {
        __int128 l = (__int128)x.p * v, r = (__int128)u * x.q;
        return strict ? l > r : l >= r;
      };
      if (f({0, 1})) continue;
      Fr wl{0, 1}, wh{1, 0};
      rep(q, 1, N + 1) rep(p, 0, N + 1) if (gcd(p, q) == 1) {
        Fr x{p, q};
        if (f(x) && less_(x, wh)) wh = x;
        if (!f(x) && less_(wl, x)) wl = x;
      }
      ll calls = 0;
      auto [lo, hi] = fracSearch([&](Fr x) {
        ++calls;
        CHECK(x.p <= N && x.q <= N && x.q >= 1);
        return f(x);
      }, N);
      CHECK(lo.p == wl.p && lo.q == wl.q, "N=%lld u/v=%lld/%lld lo %lld/%lld want %lld/%lld", N, u, v, lo.p, lo.q,
            wl.p, wl.q);
      CHECK(hi.p == wh.p && hi.q == wh.q, "N=%lld u/v=%lld/%lld hi %lld/%lld want %lld/%lld", N, u, v, hi.p, hi.q,
            wh.p, wh.q);
    }
    for (ll N : {1000000000LL, 999999937LL, 123456LL}) {  // sqrt(2), large N
      ll calls = 0;
      auto [lo, hi] = fracSearch([&](Fr x) { ++calls; return (__int128)x.p * x.p >= (__int128)2 * x.q * x.q; }, N);
      CHECK((__int128)lo.p * lo.p < (__int128)2 * lo.q * lo.q && (__int128)hi.p * hi.p >= (__int128)2 * hi.q * hi.q);
      CHECK((__int128)hi.p * lo.q - (__int128)lo.p * hi.q == 1);  // neighbours
      CHECK(lo.p + hi.p > N || lo.q + hi.q > N);  // nothing in between fits
      CHECK(calls < 4000, "%lld", calls);
    }
    {  // always true except 0: smallest positive fraction is 1/N
      auto [lo, hi] = fracSearch([](Fr x) { return x.p > 0; }, 1000);
      CHECK(lo.p == 0 && hi.p == 1 && hi.q == 1000);
      auto [l2, h2] = fracSearch([](Fr x) { return x.p > 5 * x.q; }, 4);  // nothing true fits
      CHECK(h2.p == 1 && h2.q == 0 && l2.p == 4 && l2.q == 1);
    }
  }
}
