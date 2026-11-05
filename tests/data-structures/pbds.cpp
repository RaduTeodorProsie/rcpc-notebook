#include "data-structures/pbds.h"
#include "testlib.h"
int main() {
  oset<int> s;
  set<int> ref;
  rep(q, 0, 20000) {
    int x = rnd(0, 1000);
    if (rnd(0, 1)) s.insert(x), ref.insert(x);
    else s.erase(x), ref.erase(x);
    int y = rnd(0, 1001);
    CHECK((int)s.order_of_key(y) == (int)distance(ref.begin(), ref.lower_bound(y)));
    if (sz(ref)) {
      int k = rnd(0, sz(ref) - 1);
      CHECK(*s.find_by_order(k) == *next(ref.begin(), k));
    }
  }
  hmap<ll, int> h;
  map<ll, int> m;
  rep(q, 0, 50000) {
    ll k = rnd(-1e18, 1e18) & ~1023ll;
    if (rnd(0, 3) == 0) k = rnd(0, 100);
    h[k]++, m[k]++;
  }
  for (auto [k, v] : m) CHECK(h[k] == v);
  CHECK((int)h.size() == sz(m));
}
