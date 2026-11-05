#include "strings/kmp.h"
#include "strings/zfunc.h"
#include "strings/manacher.h"
#include "strings/hashing.h"
#include "strings/lyndon.h"
#include "testlib.h"
int main() {
  ull B = rnd(256, M - 1);
  rep(it, 0, 3000) {
    int n = rnd(0, 40);
    string s = rstr(n, 'a', "abc"[rnd(0, 2)]);
    string pat = rstr(rnd(1, 4), 'a', 'c');
    // prefix function
    vi p = pi(s);
    rep(i, 0, n) {
      int w = 0;
      rep(k, 1, i + 1) if (s.substr(0, k) == s.substr(i + 1 - k, k)) w = k;
      CHECK(p[i] == w);
    }
    vi m = match(s, pat), want;
    rep(i, 0, n - sz(pat) + 1) if (s.substr(i, sz(pat)) == pat) want.push_back(i);
    CHECK(m == want);
    int per = n;
    rep(q, 1, n + 1) {
      bool ok = true;
      rep(i, 0, n - q) ok &= s[i] == s[i + q];
      if (ok) { per = q; break; }
    }
    CHECK(period(s) == (n ? per : 0));
    // z-function
    vi z = zfunc(s);
    rep(i, 1, n) {
      int w = 0;
      while (i + w < n && s[w] == s[i + w]) ++w;
      CHECK(z[i] == w);
    }
    // manacher
    auto d = manacher(s);
    auto isPal = [&](int l, int r) {  // [l, r)
      rep(i, 0, (r - l) / 2) if (s[l + i] != s[r - 1 - i]) return false;
      return true;
    };
    rep(i, 0, n) {
      int odd = 0, even = 0;
      while (i - odd >= 0 && i + odd < n && isPal(i - odd, i + odd + 1)) ++odd;
      while (i - even - 1 >= 0 && i + even < n && isPal(i - even - 1, i + even + 1)) ++even;
      CHECK(d[0][i] == odd && d[1][i] == even, "s=%s i=%d", s.c_str(), i);
    }
    // hashing: equal substrings iff equal hashes (with overwhelming probability)
    Hash h(s, B);
    rep(q, 0, 20) {
      if (n == 0) break;
      int l1 = rnd(0, n - 1), l2 = rnd(0, n - 1), len = rnd(0, n - max(l1, l2));
      CHECK((h.get(l1, l1 + len) == h.get(l2, l2 + len)) == (s.substr(l1, len) == s.substr(l2, len)));
    }
    // duval / min rotation
    if (n) {
      vi f = duval(s);
      CHECK(f[0] == 0);
      vector<string> w;
      rep(i, 0, sz(f)) w.push_back(s.substr(f[i], (i + 1 < sz(f) ? f[i + 1] : n) - f[i]));
      rep(i, 0, sz(w)) {
        rep(k, 1, sz(w[i])) CHECK(w[i] < w[i].substr(k));
        if (i) CHECK(w[i - 1] >= w[i]);
      }
      string best = s;
      rep(k, 0, n) best = min(best, s.substr(k) + s.substr(0, k));
      int r = minRotation(s);
      CHECK(s.substr(r) + s.substr(0, r) == best);
    }
  }
}
