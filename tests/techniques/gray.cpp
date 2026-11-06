#include "techniques/gray.h"
#include "testlib.h"
// Reflected k-ary Gray code by its definition: for each top digit t, the
// list for n - 1 digits, reversed when t is odd. Digit 0 first.
vector<vi> refl(int n, int k) {
  if (n == 0) return {{}};
  auto s = refl(n - 1, k);
  vector<vi> r;
  rep(t, 0, k) rep(j, 0, sz(s)) {
    vi w = t % 2 ? s[sz(s) - 1 - j] : s[j];
    w.push_back(t);
    r.push_back(w);
  }
  return r;
}
int main() {
  rep(n, 0, 16) {  // binary
    ll N = 1LL << n;
    vector<bool> seen(N);
    rep(i, 0, N) {
      ll g = gray(i);
      CHECK(g < N && !seen[g]);
      seen[g] = true;
      CHECK(igray(g) == i);
      ll h = gray((i + 1) % N), diff = g ^ h;
      if (n > 0) {
        CHECK(__builtin_popcountll(diff) == 1, "n=%d i=%lld", n, i);
        int bit = i + 1 < N ? __builtin_ctzll(i + 1) : n - 1;
        CHECK(diff == 1LL << bit, "n=%d i=%lld", n, i);
      }
    }
    ll x = rnd(0, N - 1);  // start anywhere
    set<ll> s;
    rep(i, 0, N) s.insert(x ^ gray(i));
    CHECK(sz(s) == N && (x ^ gray(0)) == x);
  }
  rep(it, 0, 1000) CHECK(igray(gray(it * 1234567891LL)) == it * 1234567891LL);
  rep(k, 1, 6) rep(n, 0, 6) {  // k-ary
    if (pow(k, n) > 5000) continue;
    auto want = refl(n, k);
    set<vi> s;
    rep(m, 0, sz(want)) {
      vi g = kgray(m, n, k);
      CHECK(g == want[m], "k=%d n=%d m=%d", k, n, m);
      s.insert(g);
      if (m) {
        int ch = 0;
        rep(i, 0, n) if (g[i] != want[m - 1][i]) {
          ++ch;
          CHECK(abs(g[i] - want[m - 1][i]) == 1);
        }
        CHECK(ch == 1);
      }
    }
    CHECK(sz(s) == sz(want));
  }
  rep(n, 1, 15) rep(k, 0, n + 1) {  // k-subsets
    auto c = combs(n, k);
    ll want = 1;
    rep(i, 0, k) want = want * (n - i) / (i + 1);
    CHECK(sz(c) == want, "n=%d k=%d", n, k);
    set<ll> s(all(c));
    CHECK(sz(s) == sz(c));
    for (ll m : c) CHECK(__builtin_popcountll(m) == k && m < (1LL << n));
    rep(i, 0, sz(c)) {
      ll d = c[i] ^ c[(i + 1) % sz(c)];
      if (sz(c) > 1) CHECK(__builtin_popcountll(d) == 2, "n=%d k=%d i=%d", n, k, i);
    }
  }
  rep(n, 0, 9) {  // permutations
    auto p = sjt(n);
    ll f = 1;
    rep(i, 1, n + 1) f *= i;
    CHECK(sz(p) == f, "n=%d", n);
    set<vi> s(all(p));
    CHECK(sz(s) == f);
    rep(i, 1, sz(p)) {
      vi d;
      rep(j, 0, n) if (p[i][j] != p[i - 1][j]) d.push_back(j);
      CHECK(sz(d) == 2 && d[1] == d[0] + 1 && p[i][d[0]] == p[i - 1][d[1]] &&
                p[i][d[1]] == p[i - 1][d[0]],
            "n=%d i=%d", n, i);
    }
  }
}
