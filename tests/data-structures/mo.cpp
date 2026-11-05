#include "data-structures/mo.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {
    int n = rnd(1, 200), q = rnd(1, 200);
    vi a(n);
    for (int& x : a) x = rnd(0, 20);
    vector<pii> Q(q);
    for (auto& [l, r] : Q) l = rnd(0, n), r = rnd(0, n), l > r ? swap(l, r) : void();
    vi cnt(21);
    int distinct = 0;
    auto res = mo(n, Q,
      [&](int i) { distinct += cnt[a[i]]++ == 0; },
      [&](int i) { distinct -= --cnt[a[i]] == 0; },
      [&]() { return distinct; });
    rep(i, 0, q) {
      set<int> s(a.begin() + Q[i].first, a.begin() + Q[i].second);
      CHECK(res[i] == sz(s));
    }
  }
}
