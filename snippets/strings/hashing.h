/**
 * Name: String hashing
 * Description: *Needs `__int128`* (the product in `mul`).
 *   Polynomial hash modulo $2^61 - 1$. Pick the base
 *   at random, e.g. `rng() % (M - 256) + 256`.
 * Time: $O(n)$ build, $O(1)$ query of $[l, r)$
 */
#pragma once
using ull = unsigned long long;
const ull M = (1ull << 61) - 1;
ull mul(ull a, ull b) {
  __uint128_t c = (__uint128_t)a * b;
  ull r = (ull)(c & M) + (ull)(c >> 61);
  return r >= M ? r - M : r;
}
struct Hash {
  vector<ull> h, pw;
  Hash(const string& s, ull B)
      : h(sz(s) + 1), pw(sz(s) + 1, 1) {
    rep(i, 0, sz(s)) {
      h[i + 1] = (mul(h[i], B) + (unsigned char)s[i]) % M;
      pw[i + 1] = mul(pw[i], B);
    }
  }
  ull get(int l, int r) {
    return (h[r] + M - mul(h[l], pw[r - l])) % M;
  }
};
