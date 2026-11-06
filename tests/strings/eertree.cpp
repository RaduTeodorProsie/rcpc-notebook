#include "strings/eertree.h"
#include "testlib.h"
int main() {
  rep(it, 0, 2000) {
    int n = rnd(0, 40);
    string s = rstr(n, 'a', "abc"[rnd(0, 2)]);
    Eertree e;
    map<string, int> cnt;
    rep(i, 0, n) {
      e.add(s[i]);
      int longest = 0;
      rep(l, 0, i + 1) {
        string t = s.substr(l, i + 1 - l);
        if (t == string(t.rbegin(), t.rend())) { longest = max(longest, sz(t)); cnt[t]++; }
      }
      CHECK(e.len[e.last] == longest);
    }
    e.count();
    CHECK(sz(e.len) - 2 == sz(cnt));
    ll total = 0;
    rep(v, 2, sz(e.len)) total += e.occ[v];
    ll want = 0;
    for (auto& [t, c] : cnt) want += c;
    CHECK(total == want);
    // palindromes ending at each position, and the fewest palindromes s splits into
    auto isPal = [&](int l, int r) {  // s[l..r)
      for (int a = l, b = r - 1; a < b; ++a, --b) if (s[a] != s[b]) return false;
      return true;
    };
    auto ends = palEnds(s);
    CHECK(sz(ends) == n);
    rep(i, 0, n) {
      int c = 0;
      rep(l, 0, i + 1) c += isPal(l, i + 1);
      CHECK(ends[i] == c);
    }
    vi dp(n + 1, INT_MAX);
    dp[0] = 0;
    rep(i, 1, n + 1) rep(l, 0, i) if (isPal(l, i)) dp[i] = min(dp[i], dp[l] + 1);
    CHECK(minPalSplit(s) == dp[n], "s=%s got %d want %d", s.c_str(), minPalSplit(s), dp[n]);
  }
  rep(it, 0, 300) {  // longer strings with long runs of equal differences (series links matter)
    int n = rnd(1, 400);
    string s;
    while (sz(s) < n) {
      string blk = rstr(rnd(1, 4), 'a', 'b');
      int rep_ = rnd(1, 20);
      while (rep_-- && sz(s) < n) s += blk;
    }
    n = sz(s);  // the last block may overshoot
    auto isPal = [&](int l, int r) {
      for (int a = l, b = r - 1; a < b; ++a, --b) if (s[a] != s[b]) return false;
      return true;
    };
    vi dp(n + 1, INT_MAX);
    dp[0] = 0;
    rep(i, 1, n + 1) rep(l, 0, i) if (isPal(l, i)) dp[i] = min(dp[i], dp[l] + 1);
    CHECK(minPalSplit(s) == dp[n], "n=%d got %d want %d s=%s", n, minPalSplit(s), dp[n], s.c_str());
  }
  {  // speed: a long string
    string s = rstr(300000, 'a', 'b');
    CHECK(minPalSplit(s) > 0 && sz(palEnds(s)) == 300000);
    // all equal: every prefix has n palindromic suffixes, so plain suffix links
    // would be O(n^2); series links keep it O(n log n)
    string a(300000, 'a'), ab;
    CHECK(minPalSplit(a) == 1);
    rep(i, 0, 100000) ab += "aab";
    CHECK(minPalSplit(ab) > 0);
  }
}
