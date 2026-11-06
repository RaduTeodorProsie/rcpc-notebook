/**
 * Name: Ternary and golden-section search
 * Description: `ternInt(lo, hi, f)` is the smallest $x$ in
 *   $[l o, h i]$ where $f$ is maximal, if $f$ strictly increases
 *   up to its maximum and never increases after it (a flat top is
 *   fine, flat parts elsewhere are not). It binary searches for
 *   the first $x$ with $f(x) >= f(x + 1)$. `golden(a, b, f)` is
 *   the same on reals: it keeps two probes at the golden ratio
 *   points, so each step reuses one value and costs a single call
 *   of $f$; the interval shrinks by $0.618$ per step. Minimum:
 *   negate $f$.
 * Time: $O(log(h i - l o))$ calls, `golden` `it` calls
 */
#pragma once
template <class F> ll ternInt(ll lo, ll hi, F f) {
  while (lo < hi) {
    ll m = lo + (hi - lo) / 2;
    if (f(m) < f(m + 1)) lo = m + 1;
    else hi = m;
  }
  return lo;
}
template <class F>
double golden(double a, double b, F f, int it = 100) {
  const double r = (sqrt(5.0) - 1) / 2;
  double x1 = b - r * (b - a), x2 = a + r * (b - a);
  double f1 = f(x1), f2 = f(x2);
  while (it--)
    if (f1 < f2) {
      a = x1, x1 = x2, f1 = f2;
      x2 = a + r * (b - a), f2 = f(x2);
    } else {
      b = x2, x2 = x1, f2 = f1;
      x1 = b - r * (b - a), f1 = f(x1);
    }
  return (a + b) / 2;
}
