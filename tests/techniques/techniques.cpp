#include "techniques/matrix.h"
#include "techniques/parallelbs.h"
#include "techniques/splitrebuild.h"
#include "testlib.h"
int main() {
  rep(it, 0, 200) {  // matrix: linear recurrence
    int k = rnd(1, 4);
    vector<ll> c = rvec(k, 0, 5), a = rvec(k, 0, 5);
    ll n = rnd(0, 60);
    vector<ll> seq = a;  // seq[i] = a_i for i < k
    while (sz(seq) <= n + k) {
      ll v = 0;
      rep(j, 0, k) v = (v + c[j] * seq[sz(seq) - 1 - j]) % MM;
      seq.push_back(v);
    }
    Mat T(k, vector<ll>(k));
    rep(j, 0, k) T[0][j] = c[j];
    rep(j, 1, k) T[j][j - 1] = 1;
    Mat st(k, vector<ll>(1));
    rep(j, 0, k) st[j][0] = a[k - 1 - j];  // (a_{k-1}, ..., a_0)
    Mat r = mul(mpow(T, n), st);
    CHECK(r[k - 1][0] == seq[n]);
  }
  rep(it, 0, 200) {  // parallel binary search
    int n = rnd(1, 8), T = rnd(0, 40), Q = rnd(1, 30);
    vector<pii> ev(T);
    for (auto& [x, w] : ev) x = rnd(0, n - 1), w = rnd(0, 3);
    vector<pii> qs(Q);
    for (auto& [x, need] : qs) x = rnd(0, n - 1), need = rnd(0, 20);
    vector<ll> cur(n);
    vi p = parallelBS(Q, T, [&] { fill(all(cur), 0); },
        [&](int i) { cur[ev[i].first] += ev[i].second; },
        [&](int q) { return cur[qs[q].first] >= qs[q].second; });
    rep(q, 0, Q) {
      vector<ll> c(n);
      int want = 0;  // max t with not ok after t events
      bool okNow = c[qs[q].first] >= qs[q].second;
      if (!okNow) {
        rep(t, 0, T) {
          c[ev[t].first] += ev[t].second;
          if (c[qs[q].first] >= qs[q].second) break;
          want = t + 1;
        }
        CHECK(p[q] == want);
      } else CHECK(p[q] == 0);
    }
  }
  rep(it, 0, 200) {  // split and rebuild
    int n = rnd(1, 30);
    vector<ll> a = rvec(n, -9, 9);
    SplitRebuild s(a);
    int Q = 100, B = 10;
    rep(q, 0, Q) {
      if (q % B == 0) s.rebuild();
      int l = rnd(0, n), r = rnd(0, n);
      if (l > r) swap(l, r);
      if (rnd(0, 1)) s.reverse(l, r), reverse(a.begin() + l, a.begin() + r);
      else {
        ll w = 0;
        rep(i, l, r) w += a[i];
        CHECK(s.sum(l, r) == w);
      }
    }
    s.rebuild();
    CHECK(s.a == a);
  }
}
