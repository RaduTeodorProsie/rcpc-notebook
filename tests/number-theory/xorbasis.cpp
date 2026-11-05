#include "number-theory/xorbasis.h"
#include "testlib.h"
int main() {
  rep(it, 0, 3000) {
    int n = rnd(0, 10), bits = rnd(1, 64);
    vector<unsigned long long> v(n);
    for (auto& x : v) x = bits == 64 ? trng() : trng() % (1ull << bits);
    set<unsigned long long> span{0};
    XorBasis b;
    rep(i, 0, n) {
      bool fresh = !span.count(v[i]);
      CHECK(b.add(v[i]) == fresh);
      set<unsigned long long> nxt = span;
      for (auto s : span) nxt.insert(s ^ v[i]);
      span = nxt;
    }
    unsigned long long q = trng();
    unsigned long long best = 0;
    for (auto s : span) best = max(best, s ^ q);
    CHECK(b.best(q) == best);
  }
}
