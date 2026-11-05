/**
 * Name: Hungarian algorithm
 * Description: Min-cost assignment: every row (worker) gets a
 *   different column (job). $a$ is $n times m$ with $n <= m$
 *   (transpose otherwise). Returns (cost, column of each row).
 *   Maximum weight: pass $a_(i j) = -w_(i j)$ and negate the cost.
 *   Forbidden pairs: a big cost such as $10^15$; if the answer
 *   uses one, no valid assignment exists.
 * Time: $O(n^2 m)$
 */
#pragma once
pair<ll, vi> hungarian(const vector<vector<ll>>& a) {
  int n = sz(a), m = sz(a[0]);
  vector<ll> u(n + 1), v(m + 1);
  vi p(m + 1), way(m + 1);
  rep(i, 1, n + 1) {
    p[0] = i;
    int j0 = 0;
    vector<ll> mn(m + 1, LLONG_MAX);
    vector<bool> used(m + 1);
    do {
      used[j0] = true;
      int i0 = p[j0], j1 = 0;
      ll delta = LLONG_MAX;
      rep(j, 1, m + 1) if (!used[j]) {
        ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < mn[j]) mn[j] = cur, way[j] = j0;
        if (mn[j] < delta) delta = mn[j], j1 = j;
      }
      rep(j, 0, m + 1) {
        if (used[j]) u[p[j]] += delta, v[j] -= delta;
        else mn[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    do {
      int j1 = way[j0];
      p[j0] = p[j1], j0 = j1;
    } while (j0);
  }
  vi match(n);
  rep(j, 1, m + 1) if (p[j]) match[p[j] - 1] = j - 1;
  return {-v[0], match};
}
