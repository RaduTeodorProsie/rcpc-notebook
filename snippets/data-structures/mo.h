/**
 * Name: Mo's algorithm
 * Description: Answers offline queries $[l, r)$ given `add(i)`,
 *   `del(i)` (move the window by one position) and `get()`.
 * Time: $O((n + q) sqrt(n))$ calls of add/del
 */
#pragma once
template <class A, class D, class G>
vector<ll> mo(int n, const vector<pii>& Q, A add, D del,
              G get) {
  int B = max(1, int(n / sqrt(max(1, sz(Q)))));
  vi ord(sz(Q));
  iota(all(ord), 0);
  sort(all(ord), [&](int a, int b) {
    int x = Q[a].first / B, y = Q[b].first / B;
    if (x != y) return x < y;
    return x & 1 ? Q[a].second > Q[b].second
                 : Q[a].second < Q[b].second;
  });
  vector<ll> res(sz(Q));
  int L = 0, R = 0;
  for (int q : ord) {
    auto [l, r] = Q[q];
    while (R < r) add(R++);
    while (L > l) add(--L);
    while (R > r) del(--R);
    while (L < l) del(L++);
    res[q] = get();
  }
  return res;
}
