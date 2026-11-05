/**
 * Name: Floor sum
 * Description: $sum_(i=0)^(n-1) floor((a i + b) \/ m)$ for any signed
 *   $a, b$ and $m > 0$. Intermediate values must fit in `ull`.
 * Time: $O(log m)$
 */
#pragma once
ll floorSum(ll n, ll m, ll a, ll b) {
  ll ans = 0;
  if (a < 0) {
    ll a2 = (a % m + m) % m;
    ans -= (__int128)n * (n - 1) / 2 * ((a2 - a) / m);
    a = a2;
  }
  if (b < 0) {
    ll b2 = (b % m + m) % m;
    ans -= n * ((b2 - b) / m);
    b = b2;
  }
  unsigned long long N = n, M = m, A = a, B = b, r = 0;
  while (true) {
    if (A >= M) r += N * (N - 1) / 2 * (A / M), A %= M;
    if (B >= M) r += N * (B / M), B %= M;
    unsigned long long y = A * N + B;
    if (y < M) break;
    N = y / M, B = y % M;
    swap(M, A);
  }
  return ans + (ll)r;
}
