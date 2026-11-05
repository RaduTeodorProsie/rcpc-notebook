#include "dp/slope.h"
#include "testlib.h"
// Brute force: f on integer points of [-X, X]; outside, extend linearly (slopes stay valid).
const int X = 200;
const ll INF = 1e12;  // brute-force value outside the domain
int main() {
  rep(it, 0, 3000) {
    Slope s;
    vector<ll> f(2 * X + 1, 0);
    auto at = [&](ll x) { return f[x + X]; };
    int ops = rnd(1, 12);
    if (rnd(0, 1)) {  // start at "0 at a, infinity elsewhere", infinity = K * |x - a|
      ll a = rnd(-5, 5), K = 30;
      rep(k, 0, K) s.pushL(a), s.pushR(a);
      rep(x, -X, X + 1) f[x + X] = K * llabs(x - a);
    }
    rep(o, 0, ops) {
      int ty = rnd(0, 7);
      ll a = rnd(-8, 8), b = a + rnd(0, 4);
      vector<ll> g = f;
      rep(x, -X, X + 1) {
        ll& v = g[x + X];
        if (ty == 0) v += a;
        if (ty == 1) v += max(0LL, x - a);
        if (ty == 2) v += max(0LL, a - x);
        if (ty == 3) v += llabs(x - a);
        if (ty == 4) { v = INF; rep(y, -X, x + 1) v = min(v, at(y)); }
        if (ty == 5) { v = INF; rep(y, x, X + 1) v = min(v, at(y)); }
        if (ty == 6) v = (x - a >= -X && x - a <= X) ? at(x - a) : INF;
        if (ty == 7) { v = INF; rep(y, x - b, x - a + 1) if (y >= -X && y <= X) v = min(v, at(y)); }
      }
      if (ty == 0) s.addConst(a);
      if (ty == 1) s.addRight(a);
      if (ty == 2) s.addLeft(a);
      if (ty == 3) s.addAbs(a);
      if (ty == 4) s.prefixMin();
      if (ty == 5) s.suffixMin();
      if (ty == 6) s.shift(a);
      if (ty == 7) s.window(a, b);
      for (ll& v : g) v = min(v, INF);
      f = g;
    }
    // compare away from the borders, where shifts made the brute force inexact
    ll mn = LLONG_MAX;
    rep(x, -20, 21) {
      Slope c = s;
      CHECK(c.eval(x) == at(x), "it=%d x=%d got %lld want %lld", it, x, Slope(s).eval(x), at(x));
      mn = min(mn, at(x));
    }
    CHECK(s.mn == mn || s.topL() < -20 || s.topR() > 20);
  }
  // the classic example: make a non-decreasing
  rep(it, 0, 500) {
    int n = rnd(0, 30);
    auto a = rvec(n, 0, 10);
    Slope s;
    for (ll x : a) s.addAbs(x), s.prefixMin();
    vector<ll> D(11, 0);
    for (ll x : a) {
      vector<ll> E(11);
      ll run = LLONG_MAX;
      rep(v, 0, 11) run = min(run, D[v]), E[v] = run + llabs(x - v);
      D = E;
    }
    CHECK(s.mn == (n ? *min_element(all(D)) : 0));
  }
}
