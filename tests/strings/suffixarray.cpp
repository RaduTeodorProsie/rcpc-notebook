#include "strings/suffixarray.h"
#include "testlib.h"
int main() {
  rep(it, 0, 2000) {
    int n = rnd(0, 40);
    string s = rstr(n, 'a', "abz"[rnd(0, 2)]);
    vi sa = suffixArray(s), want(n);
    iota(all(want), 0);
    sort(all(want), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    CHECK(sa == want, "s=%s", s.c_str());
    auto common = [&](int a, int b) { int k = 0; while (max(a, b) + k < n && s[a + k] == s[b + k]) ++k; return k; };
    vi lcp = lcpArray(s, sa);
    rep(i, 0, n - 1) CHECK(lcp[i] == common(sa[i], sa[i + 1]));
    set<string> subs;
    rep(i, 0, n) rep(j, i + 1, n + 1) subs.insert(s.substr(i, j - i));
    CHECK(distinctSubstrings(s) == sz(subs));
    if (n) {
      SuffixLCP q(s);
      rep(t, 0, 20) {
        int a = rnd(0, n - 1), b = rnd(0, n - 1);
        CHECK(q.lcp(a, b) == common(a, b));
      }
    }
    string t = rstr(rnd(0, 30), 'a', 'c');
    int best = 0;
    rep(i, 0, n) rep(j, 0, sz(t)) {
      int k = 0;
      while (i + k < n && j + k < sz(t) && s[i + k] == t[j + k]) ++k;
      best = max(best, k);
    }
    auto [len, at] = commonSubstring(s, t);
    CHECK(len == best);
    if (len) CHECK(t.find(s.substr(at, len)) != string::npos);
  }
  string big(200000, 'a');
  CHECK(distinctSubstrings(big) == 200000);
}
