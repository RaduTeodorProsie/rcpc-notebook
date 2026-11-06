/**
 * Name: Extended Euclid and CRT
 * Description: *Needs `__int128`* (`crt`: $t m$ can exceed
 *   $2^63$). `euclid` finds $x, y$ with $a x + b y = gcd(a, b)$.
 *   `crt` solves $x equiv a space (mod m)$, $x equiv b space (mod n)$,
 *   returning $(x, op("lcm")(m, n))$ with $0 <= x < op("lcm")$, or
 *   $(-1, -1)$. Fold it over a list for more congruences.
 * Time: $O(log min(m, n))$
 */
#pragma once
ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
pair<ll, ll> crt(ll a, ll m, ll b, ll n) {
  ll x, y, g = euclid(m, n, x, y);
  if ((b - a) % g) return {-1, -1};
  ll l = m / g * n;
  ll t = (__int128)(b - a) / g * x % (n / g);
  ll r = ((a + (__int128)t * m) % l + l) % l;
  return {r, l};
}
