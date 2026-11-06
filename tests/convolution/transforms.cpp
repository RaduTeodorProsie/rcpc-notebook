#include "convolution/subsets.h"
#include "convolution/supersets.h"
#include "convolution/xorT.h"
#include "convolution/divisors.h"
#include "convolution/multiples.h"
#include "testlib.h"
using V = vector<ll>;
V convolve(V a, V b, void (*T)(V&, bool)) {
  T(a, false), T(b, false);
  rep(i, 0, sz(a)) a[i] *= b[i];
  T(a, true);
  return a;
}
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
    V gs = a;
    supersets(gs);
    rep(m, 0, n) {
      ll s = 0, t = 0;
      rep(x, 0, n) if ((x & m) == x) s += a[x];
      rep(x, 0, n) if ((x & m) == m) t += a[x];
      CHECK(g[m] == s && gs[m] == t);
    }
    subsets(g, true), supersets(gs, true);
    CHECK(g == a && gs == a);
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
    V hm = c;
    multiples(hm);
    rep(k, 1, N + 1) {
      ll s = 0;
      for (int x = k; x <= N; x += k) s += c[x];
      CHECK(hm[k] == s);
    }
    divisors(h, true), multiples(hm, true);
    CHECK(h == c && hm == c);
  }
}
