#include "testlib.h"
int main() {
  rep(it, 0, 300) {
    int n = rnd(1, 200), q = rnd(1, 200);
    vi a(n);
    for (int& x : a) x = rnd(0, 20);
    vector<array<int, 3>> Q(q), orig;
    rep(i, 0, q) {
      int l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      Q[i] = {l, r, i};
    }
    orig = Q;
    vi cnt(21), ans(q);
    int distinct = 0;
    auto add = [&](int i) { distinct += cnt[a[i]]++ == 0; };
    auto del = [&](int i) { distinct -= --cnt[a[i]] == 0; };
    auto get = [&]() { return distinct; };
#include "data-structures/mo.frag"
    for (auto [l, r, id] : orig) {
      set<int> s(a.begin() + l, a.begin() + r);
      CHECK(ans[id] == sz(s));
    }
  }
}
