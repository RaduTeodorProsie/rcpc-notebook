/**
 * Name: Slope trick
 * Description: Keep a convex piecewise linear $f(x)$ as a heap of
 *   breakpoints (slope changes by 1 at each) plus its minimum.
 *   Example: minimum $sum |a_i - b_i|$ over non-decreasing $b$.
 *   Adding $|x - a|$ pushes $a$ twice; taking prefix minima
 *   drops the right side (pop the top).
 * Time: $O(n log n)$
 */
#pragma once
ll makeNonDecreasing(const vector<ll>& a) {
  priority_queue<ll> pq; // breakpoints left of the minimum
  ll ans = 0;
  for (ll x : a) {
    pq.push(x);
    if (pq.top() > x) {
      ans += pq.top() - x;
      pq.pop(), pq.push(x);
    }
  }
  return ans;
}
