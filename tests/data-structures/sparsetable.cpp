#include "data-structures/sparsetable.h"
#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 100);
    auto a = rvec(n, -1e9, 1e9);
    RMQ<ll> r(a);
    rep(q, 0, 200) {
      int l = rnd(0, n - 1), h = rnd(l + 1, n);
      CHECK(r.query(l, h) == *min_element(a.begin() + l, a.begin() + h));
    }
  }
}
