/**
 * Name: Miller-Rabin
 * Description: Deterministic primality test for all 64-bit
 *   integers. `powm` is modular power for any modulus.
 * Time: $7$ modular exponentiations
 */
#pragma once
using ull = unsigned long long;
ull mulm(ull a, ull b, ull m) {
  return (__uint128_t)a * b % m;
}
ull powm(ull b, ull e, ull m) {
  ull r = 1 % m;
  for (b %= m; e; e >>= 1, b = mulm(b, b, m))
    if (e & 1) r = mulm(r, b, m);
  return r;
}
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull d = n - 1;
  int s = __builtin_ctzll(d);
  d >>= s;
  for (ull a : {2, 325, 9375, 28178, 450775, 9780504,
                1795265022}) {
    ull x = powm(a % n, d, n);
    if (x == 0 || x == 1 || x == n - 1) continue;
    for (int i = 1; i < s && x != n - 1; ++i)
      x = mulm(x, x, n);
    if (x != n - 1) return false;
  }
  return true;
}
