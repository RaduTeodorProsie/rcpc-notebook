#include "strings/sam.h"
#include "testlib.h"
int main() {
  rep(it, 0, 1500) {
    int n = rnd(0, 30);
    string s = rstr(n, 'a', "abd"[rnd(0, 2)]);
    SAM a(s);
    a.countOcc();
    CHECK(sz(a.len) <= max(1, 2 * n));
    set<string> subs;
    rep(i, 0, n) rep(j, i + 1, n + 1) subs.insert(s.substr(i, j - i));
    CHECK(distinct(a) == sz(subs));
    rep(q, 0, 20) {
      string t = rstr(rnd(1, 4), 'a', 'd');
      int occ = 0;
      rep(i, 0, n - sz(t) + 1) occ += s.substr(i, sz(t)) == t;
      CHECK(occurrences(a, t) == occ);
    }
    string t = rstr(rnd(0, 30), 'a', 'c');
    int best = 0;
    rep(i, 0, n) rep(j, 0, sz(t)) {
      int k = 0;
      while (i + k < n && j + k < sz(t) && s[i + k] == t[j + k]) ++k;
      best = max(best, k);
    }
    CHECK(longestCommon(a, t) == best);
    vector<string> v(all(subs));
    rep(q, 0, min(sz(v), 10)) {
      int k = rnd(1, sz(v));
      CHECK(kthDistinct(a, k) == v[k - 1]);
    }
  }
}
