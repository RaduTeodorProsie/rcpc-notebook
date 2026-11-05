#include "data-structures/staircase.h"
#include "data-structures/cht.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    Staircase s;
    vector<pair<ll, ll>> pts;
    rep(q, 0, 100) {
      if (rnd(0, 1)) {
        ll x = rnd(-15, 15), y = rnd(-15, 15);
        s.insert(x, y), pts.push_back({x, y});
      } else {
        ll x = rnd(-17, 17), want = LLONG_MIN;
        for (auto [px, py] : pts) if (px >= x) want = max(want, py);
        CHECK(s.query(x) == want);
      }
    }
  }
  rep(it, 0, 300) {
    CHT c;
    vector<pair<ll, ll>> ls;
    ll R = it < 150 ? 20 : 1000000000;
    rep(q, 0, 100) {
      if (ls.empty() || rnd(0, 1)) {
        ll k = rnd(-R, R), m = rnd(-R * R, R * R);
        c.add(k, m), ls.push_back({k, m});
      } else {
        ll x = rnd(-R, R), want = LLONG_MIN;
        for (auto [k, m] : ls) want = max(want, k * x + m);
        CHECK(c.query(x) == want);
      }
    }
  }
}
