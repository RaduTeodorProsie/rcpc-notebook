/**
 * Name: Sparse table
 * Description: Range minimum on $[a, b)$, $a < b$, for a static
 *   array. Works for any idempotent operation.
 * Time: $O(n log n)$ build, $O(1)$ query
 */
#pragma once
template <class T> struct RMQ {
  vector<vector<T>> t;
  RMQ(const vector<T>& v) : t(1, v) {
    for (int k = 1; (1 << k) <= sz(v); ++k) {
      t.emplace_back(sz(v) - (1 << k) + 1);
      rep(i, 0, sz(t[k])) t[k][i] =
        min(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
  }
  T query(int a, int b) {
    int k = __lg(b - a);
    return min(t[k][a], t[k][b - (1 << k)]);
  }
};
