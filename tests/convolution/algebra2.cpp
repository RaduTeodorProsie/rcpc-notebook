#include "convolution/berlekamp.h"
#include "number-theory/sqrtmod.h"
#include "convolution/subsetconv.h"
#include "convolution/poly.h"
#include "testlib.h"
mint rm() { return mint(rnd(0, MOD - 1)); }
int main() {
  {  // Berlekamp-Massey + linRec
    rep(it, 0, 1500) {
      int L = rnd(0, 12), T = rnd(2 * L, 2 * L + 30);
      vector<mint> c(L), s;
      for (auto& x : c) x = rnd(0, 3) ? rm() : mint(rnd(0, 2));
      if (L && rnd(0, 1)) c[L - 1] = rm() + 1;
      rep(i, 0, L) s.push_back(rnd(0, 2) ? rm() : mint(0));
      while (sz(s) < max(T, 2000)) {
        mint x = 0;
        rep(j, 0, L) x += c[j] * s[sz(s) - 1 - j];
        s.push_back(x);
      }
      vector<mint> pre(s.begin(), s.begin() + T);
      auto got = berlekamp(pre);
      CHECK(sz(got) <= L);
      // got must reproduce every given term, and (since T >= 2L) the whole sequence
      rep(i, sz(got), sz(s)) {
        mint x = 0;
        rep(j, 0, sz(got)) x += got[j] * s[i - 1 - j];
        CHECK(x == s[i], "it=%d i=%d L=%d found %d", it, i, L, sz(got));
      }
      rep(k, 0, 30) {
        ll n = rnd(0, sz(s) - 1);
        CHECK(linRec(s, got, n) == s[n], "n=%lld", n);
      }
    }
    // the shortest recurrence: brute force over all orders on tiny random sequences
    rep(it, 0, 3000) {
      int T = rnd(1, 8);
      vector<mint> s(T);
      for (auto& x : s) x = rnd(0, 2);
      int L = sz(berlekamp(s));
      // an order-l recurrence exists iff the linear system in c is solvable; check l = L - 1 fails
      // by brute force over c in {0..MOD} is impossible, so use the Hankel rank criterion instead:
      // order l works iff vector (s_l..s_{T-1}) is in the span of the l shifted columns.
      auto solvable = [&](int l) {
        if (l >= T) return true;
        vector<vector<mint>> a(T - l, vector<mint>(l + 1));
        rep(i, l, T) {
          rep(j, 0, l) a[i - l][j] = s[i - 1 - j];
          a[i - l][l] = s[i];
        }
        int r = 0, rows = sz(a);  // Gaussian elimination mod p, check consistency
        rep(col, 0, l) {
          int p = -1;
          rep(i, r, rows) if (!(a[i][col] == 0)) p = i;
          if (p < 0) continue;
          swap(a[p], a[r]);
          mint inv = a[r][col].inv();
          rep(i, 0, rows) if (i != r && !(a[i][col] == 0)) {
            mint k = a[i][col] * inv;
            rep(j, 0, l + 1) a[i][j] -= k * a[r][j];
          }
          ++r;
        }
        rep(i, r, rows) if (!(a[i][l] == 0)) return false;
        return true;
      };
      CHECK(solvable(L));
      if (L > 0) CHECK(!solvable(L - 1), "T=%d L=%d", T, L);
    }
    // Fibonacci at 1e18 vs fast doubling
    auto fib = [](auto& self, ll n) -> pair<mint, mint> {  // (F_n, F_{n+1})
      if (!n) return {0, 1};
      auto [a, b] = self(self, n / 2);
      mint c = a * (b * 2 - a), d = a * a + b * b;
      return n % 2 ? make_pair(d, c + d) : make_pair(c, d);
    };
    vector<mint> f{0, 1, 1, 2, 3, 5};
    auto c = berlekamp(f);
    CHECK(sz(c) == 2 && c[0] == 1 && c[1] == 1);
    for (ll n : {0LL, 1LL, 2LL, 90LL, 1000000007LL, (ll)1e18, LLONG_MAX})
      CHECK(linRec(f, c, n) == fib(fib, n).first, "n=%lld", n);
    CHECK(berlekamp(vector<mint>(10, 0)).empty());
    CHECK(linRec({}, {}, 5) == 0);
  }
  {  // sqrt mod p
    for (ll p = 2; p < 3000; ++p) {
      if (!isPrime(p)) continue;
      vector<bool> sq(p);
      rep(x, 0, p) sq[x * x % p] = true;
      rep(a, 0, p) {
        ll x = sqrtMod(a, p);
        if (!sq[a]) CHECK(x == -1, "p=%lld a=%d", p, a);
        else CHECK(x >= 0 && x < p && x * x % p == a, "p=%lld a=%d x=%lld", p, a, x);
      }
      CHECK(sqrtMod(-1, p) == sqrtMod(p - 1, p));
    }
    for (ll p : {998244353LL, 1000000007LL, 469762049LL, (1LL << 61) - 1, 4179340454199820289LL,
                 9223372036854775783LL}) {
      CHECK(isPrime(p));
      rep(it, 0, 300) {
        ll y = rnd(0, p - 1), a = mulm(y, y, p);
        ll x = sqrtMod(a, p);
        CHECK(x >= 0 && mulm(x, x, p) == (ull)a, "p=%lld", p);
        CHECK(x == y || x == (p - y) % p);
        ll b = rnd(1, p - 1);
        ll z = sqrtMod(b, p);
        CHECK((z == -1) == (powm(b, (p - 1) / 2, p) != 1));
        if (z >= 0) CHECK(mulm(z, z, p) == (ull)b);
      }
    }
  }
  CHECK(subsetConv({}, {}).empty());
  {  // subset convolution vs brute force
    rep(it, 0, 200) {
      int n = rnd(0, 10), N = 1 << n;
      vector<mint> a(N), b(N);
      for (auto& x : a) x = rnd(0, 3) ? rm() : mint(0);
      for (auto& x : b) x = rm();
      auto c = subsetConv(a, b);
      CHECK(sz(c) == N);
      rep(m, 0, N) {
        mint w = 0;
        for (int s = m;; s = (s - 1) & m) {
          w += a[s] * b[m ^ s];
          if (!s) break;
        }
        CHECK(c[m] == w, "n=%d m=%d", n, m);
      }
    }
  }
  {  // polynomial inverse and division
    const int M = 998244353;
    auto mulNaive = [&](const vector<ll>& a, const vector<ll>& b) {
      vector<ll> r(sz(a) && sz(b) ? sz(a) + sz(b) - 1 : 0);
      rep(i, 0, sz(a)) rep(j, 0, sz(b)) r[i + j] = (r[i + j] + a[i] * b[j]) % M;
      return r;
    };
    rep(it, 0, 300) {
      int k = rnd(1, 200), n = rnd(0, 300);
      vector<ll> a = rvec(k, 0, M - 1);
      if (!a[0]) a[0] = 1;
      auto b = inverse<M>(a, n);
      CHECK(sz(b) == n);
      auto p = mulNaive(a, b);
      rep(i, 0, n) CHECK(p[i] == (i == 0), "k=%d n=%d i=%d", k, n, i);
    }
    rep(it, 0, 500) {
      int n = rnd(0, 120), m = rnd(1, 100);
      vector<ll> a = rvec(n, 0, M - 1), b = rvec(m, 0, rnd(0, 1) ? 2 : M - 1);
      if (!b.back()) b.back() = 1;
      auto [q, r] = divMod<M>(a, b);
      if (n < m) {
        CHECK(q.empty() && r == a);
        continue;
      }
      CHECK(sz(q) == n - m + 1 && sz(r) == m - 1);
      auto qb = mulNaive(q, b);
      rep(i, 0, n) CHECK((qb[i] + (i < sz(r) ? r[i] : 0)) % M == a[i], "n=%d m=%d i=%d", n, m, i);
      for (ll x : r) CHECK(0 <= x && x < M);
    }
  }
}
