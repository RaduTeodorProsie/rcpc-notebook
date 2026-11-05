/**
 * Name: Parallel binary search
 * Description: Events $0..T-1$ happen in order, and for each
 *   query $q$, `ok(q)` is false before some time and true after
 *   (false with no events applied).
 *   Returns for each query the number $p$ of events after which
 *   `ok` is still false, maximal ($p + 1$ events make it true;
 *   $p = T$: never). Every query climbs one bit per round, from
 *   the high bit down, like binary lifting: all candidates
 *   $p + b$ are sorted, the events are replayed once from
 *   `reset()`, and each query is checked when its candidate is
 *   reached. `reset`, `apply(i)` and `ok(q)` are the problem.
 * Time: $O(log T)$ rounds of $T$ `apply`, $Q$ `ok`, a sort
 */
#pragma once
template <class R, class A, class C>
vi parallelBS(int Q, int T, R reset, A apply, C ok) {
  vi p(Q); // ok(q) is false after the first p[q] events
  for (int b = T ? 1 << __lg(T) : 0; b; b >>= 1) {
    vector<pii> c;
    rep(q, 0, Q)
      if (p[q] + b <= T) c.push_back({p[q] + b, q});
    sort(all(c));
    reset();
    int t = 0;
    for (auto [m, q] : c) {
      while (t < m) apply(t++);
      if (!ok(q)) p[q] = m;
    }
  }
  return p;
}
