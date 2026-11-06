/**
 * Name: Lagrangian relaxation (Aliens)
 * Description: $"opt"(j)$ = best cost with exactly $j$ items; we want
 *   $"opt"(k)$, or the best with at most / at least $k$. Needs
 *   $"opt"$ convex in $j$ for a minimum, concave for a maximum (check
 *   by brute force). `solve(l)` charges $l$ per item: min of cost
 *   $+ l dot$ items (maximum: max of value $- l dot$ items), and that
 *   solution's item count, *ties towards fewer items* (compare
 *   (cost, count) pairs). Larger $lambda$, fewer items: `aliens`
 *   takes the smallest $lambda$ with count $<= k$, where $k$ items
 *   are optimal too, and returns that minimum $- lambda k$. \
 *   – $C > |"opt"(j) - "opt"(j-1)|$ for all $j$; keep it tight:
 *   $lambda dot$ items must fit in `ll`. \
 *   – $lambda$ is an integer, so the slopes $"opt"(j) - "opt"(j-1)$ must
 *   be: integer costs, or scale. Real costs: search $lambda$ over
 *   doubles. \
 *   – Exactly $k$: `aliens(solve, k, -C, C)`; it must be possible.
 * Time: $O(log C)$ calls to `solve`
 */
#pragma once
template <class F> ll aliens(F solve, int k, ll lo, ll hi) {
  auto r = solve(hi); // r = solve(hi) throughout
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    auto s = solve(mid);
    if (s.second <= k) hi = mid, r = s;
    else lo = mid + 1;
  }
  return r.first - lo * k;
}
// --- uses ---
// Minimum; solve(l) = {min cost + l * items, items}.
template <class F> ll minAtMost(F f, int k, ll C) {
  return aliens(f, k, 0, C);
}
template <class F> ll minAtLeast(F f, int k, ll C) {
  return aliens(f, k, -C, 0);
}
// Maximum; solve(l) = {max value - l * items, items}.
template <class F> ll maxAtMost(F f, int k, ll C) {
  auto g = [&](ll l) { auto [v, c] = f(l); return pair(-v, c); };
  return -aliens(g, k, 0, C);
}
template <class F> ll maxAtLeast(F f, int k, ll C) {
  auto g = [&](ll l) { auto [v, c] = f(l); return pair(-v, c); };
  return -aliens(g, k, -C, 0);
}
