/**
 * Name: Fraction search
 * Description: For a predicate $f$ on fractions $p\/q >= 0$ that
 *   is false, then true ($f(0\/1)$ false): returns
 *   $(l o, h i)$, the largest fraction with $f$ false and the
 *   smallest with $f$ true, among those with $p, q <= N$
 *   ($h i = 1\/0$ if none is true). It walks down the
 *   Stern–Brocot tree, where every fraction appears once and
 *   in lowest terms: $l o, h i$ start at $0\/1, 1\/0$ and the next
 *   fraction between them is always their mediant
 *   $(p_1 + p_2)\/(q_1 + q_2)$. A long walk in one direction is
 *   done as one jump, with doubling then binary search on its
 *   length. Compare in $f$ exactly, e.g. $p\/q >= x$ as
 *   $p >= q x$ in `__int128`.
 * Usage: auto [l, h] = fracSearch([](Fr x) { // sqrt(2)
 *     return x.p * x.p >= 2 * x.q * x.q; }, N);
 * Time: $O(log^2 N)$ calls of $f$, $N <= 10^9$
 */
#pragma once
struct Fr { ll p, q; };
template <class F> pair<Fr, Fr> fracSearch(F f, ll N) {
  Fr lo{0, 1}, hi{1, 0};
  for (int side = 0, idle = 0; idle < 2; side ^= 1) {
    Fr &x = side ? lo : hi, y = side ? hi : lo;
    auto ok = [&](ll k) { // x + k y keeps f == !side?
      Fr z{x.p + k * y.p, x.q + k * y.q};
      return z.p <= N && z.q <= N && f(z) != side;
    };
    ll k = 0, s = 1;
    while (ok(k + s)) k += s, s *= 2;
    for (; s; s /= 2)
      if (ok(k + s)) k += s;
    x = {x.p + k * y.p, x.q + k * y.q};
    idle = k ? 0 : idle + 1;
  }
  return {lo, hi};
}
