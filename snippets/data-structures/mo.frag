/**
 * Name: Mo's algorithm
 * Description: Offline queries on ranges $[l, r)$ when the window
 *   can grow or shrink by one element at a time. Sort by the
 *   block of $l$ (size $B approx n \/ sqrt(q)$), then by $r$, with
 *   the direction alternating between blocks. Write `add(i)`,
 *   `del(i)` and `get()` for the problem.
 * Time: $O((n + q) sqrt(n))$ calls of add and del
 */
int B = max(1, int(n / sqrt(max(1, q))));
sort(all(Q), [&](auto& a, auto& b) { // Q[i] = {l, r, id}
  if (a[0] / B != b[0] / B) return a[0] < b[0];
  return (a[0] / B) & 1 ? a[1] > b[1] : a[1] < b[1];
});
int L = 0, R = 0; // current window [L, R)
for (auto [l, r, id] : Q) {
  while (R < r) add(R++);
  while (L > l) add(--L);
  while (R > r) del(--R);
  while (L < l) del(L++);
  ans[id] = get();
}
