#include "strings/aho.h"
#include "testlib.h"
int main() {
  rep(it, 0, 1500) {
    int k = rnd(1, 8);
    vector<string> pats(k);
    Aho a;
    vi ends(k);
    rep(i, 0, k) pats[i] = rstr(rnd(1, 4), 'a', 'c'), ends[i] = a.add(pats[i]);
    a.build();
    string t = rstr(rnd(0, 60), 'a', 'c');
    ll total = 0;
    vector<ll> h = hits(a, t);
    rep(i, 0, k) {
      ll c = 0;
      rep(j, 0, sz(t) - sz(pats[i]) + 1) c += t.substr(j, sz(pats[i])) == pats[i];
      total += c;
      CHECK(h[ends[i]] == c, "pattern %d", i);
    }
    CHECK(totalMatches(a, t) == total);
  }
}
