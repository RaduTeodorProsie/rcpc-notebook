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
  }
}
