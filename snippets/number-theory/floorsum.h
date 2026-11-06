/**
 * Name: Floor sum
 * Description: $sum_(i=0)^(n-1) floor((a i + b) \/ m)$ for any signed
 *   $a, b$ and $m > 0$, if the answer fits in `ll`. Sums are taken
 *   mod $2^64$ (overflow there is harmless); only $n(n-1)$ and
 *   $a n + b$ (for $0 <= a, b < m$) must stay below $2^64$.
 * Time: $O(log m)$
 */
#pragma once
using ull = unsigned long long;
ll floorSum(ll n, ll m, ll a, ll b) {
  ull r = 0;
  if (a < 0) {
    ll a2 = (a % m + m) % m;
    r -= ull(n) * (n - 1) / 2 * ull((a2 - a) / m);
    a = a2;
  }
  if (b < 0) {
    ll b2 = (b % m + m) % m;
    r -= ull(n) * ull((b2 - b) / m);
    b = b2;
  }
  ull N = n, M = m, A = a, B = b;
  while (true) {
    if (A >= M) r += N * (N - 1) / 2 * (A / M), A %= M;
    if (B >= M) r += N * (B / M), B %= M;
    ull y = A * N + B;
    if (y < M) break;
    N = y / M, B = y % M;
    swap(M, A);
  }
  return (ll)r;
}
