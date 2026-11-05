#include "data-structures/lichao.h"
#include "testlib.h"
int main() {
  const ll NONE = LLONG_MIN / 2;
  rep(it, 0, 400) {
    int lo = rnd(-100, 100), hi = lo + rnd(1, it < 200 ? 200 : 5);
    LiChao t(lo, hi);
    vector<tuple<Line, int, int>> ls;  // line valid on [a, b)
    ll K = it % 3 == 0 ? 1e9 : 20, M = it % 3 == 0 ? 1e12 : 50;
    rep(q, 0, 300) {
      int ty = rnd(0, 2);
      Line l{rnd(-K, K), rnd(-M, M)};
      if (ty == 0) t.add(l), ls.push_back({l, lo, hi});
      if (ty == 1) {
        int a = rnd(lo - 3, hi + 3), b = rnd(lo - 3, hi + 3);
        if (a > b) swap(a, b);
        t.addSeg(l, a, b), ls.push_back({l, a, b});
      }
      ll x = rnd(lo, hi - 1), w = NONE;
      for (auto& [ln, a, b] : ls) if (a <= x && x < b) w = max(w, ln(x));
      CHECK(t.query(x) == w, "x=%lld", x);
    }
  }
  rep(it, 0, 200) {  // minimum by negation
    int lo = rnd(0, 10), hi = lo + rnd(1, 100);
    LiChao t(lo, hi);
    vector<Line> ls;
    rep(q, 0, 100) {
      Line l{rnd(-50, 50), rnd(-500, 500)};
      t.add({-l.k, -l.m}), ls.push_back(l);
      ll x = rnd(lo, hi - 1), w = LLONG_MAX;
      for (auto& ln : ls) w = min(w, ln(x));
      CHECK(-t.query(x) == w);
    }
  }
}
