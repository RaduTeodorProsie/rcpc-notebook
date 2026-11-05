/**
 * Name: Staircase
 * Description: Insert points $(x, y)$; `query(q)` is the largest
 *   $y$ among points with $x >= q$ (`LLONG_MIN / 2` if none, so
 *   negating the answer is safe). Keeps
 *   only points that no other point beats in both coordinates, so
 *   $y$ strictly decreases as $x$ grows and the answer is the first
 *   kept point with $x >= q$. Other directions: negate $x$ (for
 *   $x <= q$) and/or $y$ (for the smallest). Offline, a Fenwick
 *   tree of suffix maxima over compressed $x$ does the same.
 * Time: amortized $O(log n)$
 */
#pragma once
struct Staircase {
  map<ll, ll> m; // x -> y
  void insert(ll x, ll y) {
    auto it = m.lower_bound(x);
    if (it != m.end() && it->second >= y) return;
    it = m.insert_or_assign(it, x, y);
    while (it != m.begin() && prev(it)->second <= y)
      m.erase(prev(it));
  }
  ll query(ll q) {
    auto it = m.lower_bound(q);
    return it == m.end() ? LLONG_MIN / 2 : it->second;
  }
};
