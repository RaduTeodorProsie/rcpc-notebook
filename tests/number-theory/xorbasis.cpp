#include "number-theory/xorbasis.h"
#include "testlib.h"
int main() {
  rep(it, 0, 3000) {
    int n = rnd(0, 10), bits = rnd(1, 64);
    vector<ull> v(n);
    for (auto& x : v) x = bits == 64 ? trng() : trng() % (1ull << bits);
    if (n && rnd(0, 2) == 0) v[rnd(0, n - 1)] = v[0] ^ (n > 1 ? v[1] : 0);  // a dependent vector
    set<ull> span{0};
    XorBasis b;
    rep(i, 0, n) {
      bool fresh = !span.count(v[i]);
      CHECK(b.add(v[i]) == fresh);
      set<ull> nxt = span;
      for (auto s : span) nxt.insert(s ^ v[i]);
      span = nxt;
    }
    CHECK(sz(span) == 1 << b.rank);
    rep(t, 0, 5) {
      ull q = rnd(0, 1) ? trng() : *next(span.begin(), rnd(0, sz(span) - 1));
      ull best = 0, worst = ULLONG_MAX;
      for (auto s : span) best = max(best, s ^ q), worst = min(worst, s ^ q);
      CHECK(b.best(q) == best && b.worst(q) == worst);
      CHECK(b.has(q) == (span.count(q) > 0));
    }
    vector<ull> sorted(all(span));
    // kth reduces the basis in place; it must keep working afterwards
    rep(t, 0, 3) {
      ull k = rnd(0, sz(sorted) - 1);
      CHECK(b.kth(k) == sorted[k], "it=%d k=%llu", it, k);
    }
    ull extra = trng() % (bits == 64 ? ULLONG_MAX : (1ull << bits));
    b.add(extra);
    set<ull> s2 = span;
    for (auto s : span) s2.insert(s ^ extra);
    vector<ull> sorted2(all(s2));
    rep(k, 0, min(sz(sorted2), 8)) CHECK(b.kth(k) == sorted2[k]);
    CHECK(b.kth(sz(sorted2) - 1) == sorted2.back() && b.best() == sorted2.back());
  }
  rep(it, 0, 300) {  // range basis vs brute force over all subsets of a[l..r)
    int n = rnd(1, 12);
    vector<ull> a(n);
    for (auto& x : a) x = trng() % (1ull << rnd(1, 12));
    RangeBasis rb;
    rep(r, 1, n + 1) {
      rb.add(a[r - 1], r - 1);
      rep(l, 0, r) {
        set<ull> span{0};
        rep(i, l, r) {
          set<ull> nx = span;
          for (auto s : span) nx.insert(s ^ a[i]);
          span = nx;
        }
        CHECK(rb.best(l) == *span.rbegin(), "it=%d l=%d r=%d", it, l, r);
      }
    }
  }
}
