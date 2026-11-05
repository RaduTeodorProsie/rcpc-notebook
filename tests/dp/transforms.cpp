#include "dp/transforms.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int B = rnd(0, 8), n = 1 << B;
    V a = rvec(n, -20, 20), b = rvec(n, -20, 20);
    V orr(n), andd(n), xr(n);
    rep(i, 0, n) rep(j, 0, n) orr[i | j] += a[i] * b[j], andd[i & j] += a[i] * b[j], xr[i ^ j] += a[i] * b[j];
    CHECK(convolve(a, b, subsets) == orr);
    CHECK(convolve(a, b, supersets) == andd);
    CHECK(convolve(a, b, xorT) == xr);
    V g = a;
    subsets(g);
    rep(m, 0, n) {
      ll s = 0;
      rep(x, 0, n) if ((x & m) == x) s += a[x];
      CHECK(g[m] == s);
    }
    int N = rnd(1, 300);
    V c = rvec(N + 1, -20, 20), d = rvec(N + 1, -20, 20);
    c[0] = d[0] = 0;
    V gc(N + 1), lc(N + 1);
    rep(i, 1, N + 1) rep(j, 1, N + 1) {
      gc[gcd(i, j)] += c[i] * d[j];
      ll l = lcm((ll)i, (ll)j);
      if (l <= N) lc[l] += c[i] * d[j];
    }
    CHECK(convolve(c, d, multiples) == gc);
    CHECK(convolve(c, d, divisors) == lc);
    V h = c;
    divisors(h);
    rep(k, 1, N + 1) {
      ll s = 0;
      rep(x, 1, k + 1) if (k % x == 0) s += c[x];
      CHECK(h[k] == s);
    }
  }
}
