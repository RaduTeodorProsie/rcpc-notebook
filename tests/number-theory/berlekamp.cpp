#include "number-theory/berlekamp.h"
#include "testlib.h"
int main() {
  rep(it, 0, 500) {
    int L = rnd(0, 10), N = 2 * L + rnd(0, 10) + 1;
    vector<mint> c(L), s(400);
    rep(i, 0, L) c[i] = rnd(0, 3) ? rnd(0, MOD - 1) : 0;
    rep(i, 0, 400) {
      if (i < L) s[i] = rnd(0, MOD - 1);
      else rep(j, 0, L) s[i] += c[j] * s[i - 1 - j];
    }
    vector<mint> pre(s.begin(), s.begin() + N);
    auto got = berlekampMassey(pre);
    CHECK(sz(got) <= L);
    rep(i, sz(got), 400) {
      mint v = 0;
      rep(j, 0, sz(got)) v += got[j] * s[i - 1 - j];
      CHECK(v == s[i], "it=%d L=%d", it, L);
    }
    rep(k, 0, 400) CHECK(kth(s, got, k) == s[k], "k=%d", k);
  }
  // Fibonacci
  auto c = berlekampMassey({0, 1, 1, 2, 3, 5});
  CHECK(sz(c) == 2 && c[0] == 1 && c[1] == 1);
  mint f = kth({0, 1}, c, 1000000000000ll), a = 0, b = 1;
  ll k = 1000000000000ll;  // fast doubling check
  function<pair<mint, mint>(ll)> fib = [&](ll n) -> pair<mint, mint> {
    if (!n) return {0, 1};
    auto [x, y] = fib(n / 2);
    mint p = x * (y * 2 - x), q = x * x + y * y;
    return n & 1 ? make_pair(q, p + q) : make_pair(p, q);
  };
  CHECK(fib(k).first == f);
  (void)a, (void)b;
}
