/**
 * Name: Convex hull trick (line container)
 * Description: Add lines $k x + m$ in any order; `query(x)` is
 *   the maximum over the lines at integer $x$. No bound on the
 *   range of $x$ (Li Chao needs one) and $O(n)$ memory. Keeps the
 *   upper envelope sorted by slope; `p` is the last $x$ where a
 *   line is on top. Minimum: add $(-k, -m)$ and negate the answer.
 *   Values must fit in `ll` at the queried $x$; add a line
 *   before the first `query`.
 * Time: $O(log n)$
 */
#pragma once
struct Ln {
  mutable ll k, m, p;
  bool operator<(const Ln& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};
struct CHT : multiset<Ln, less<>> {
  static constexpr ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floor
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y))
      isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};
