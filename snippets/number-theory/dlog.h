/**
 * Name: Discrete logarithm
 * Description: Smallest $x >= 0$ with $a^x equiv b space (mod m)$, or
 *   $-1$. Any $m >= 1$, not only primes (baby-step giant-step).
 * Time: $O(sqrt(m))$
 */
#pragma once
ll dlog(ll a, ll b, ll m) {
  a %= m, b %= m;
  ll k = 1 % m, add = 0, g;
  while ((g = __gcd(a, m)) > 1) {
    if (b == k) return add;
    if (b % g) return -1;
    b /= g, m /= g, ++add;
    k = k * (a / g) % m;
  }
  ll n = sqrtl(m) + 1, an = 1;
  rep(i, 0, n) an = an * a % m;
  unordered_map<ll, ll> vals;
  for (ll q = 0, cur = b; q <= n; ++q)
    vals[cur] = q, cur = cur * a % m;
  for (ll p = 1, cur = k; p <= n; ++p) {
    cur = cur * an % m;
    if (vals.count(cur)) return n * p - vals[cur] + add;
  }
  return -1;
}
