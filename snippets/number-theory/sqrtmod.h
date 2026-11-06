/**
 * Name: Square root mod p
 * Description: Some $x$ with $x^2 equiv a space (mod p)$, $p$ prime,
 *   or $-1$ if none ($p - x$ is the other root). A root exists
 *   iff $a^((p-1)\/2) = 1$ (Euler) or $a = 0$. Tonelli–Shanks:
 *   write $p - 1 = 2^e s$ with $s$ odd. $x = a^((s+1)\/2)$ is almost
 *   right: $x^2 = a b$ with $b = a^s$, whose order is a power of
 *   two. Each step finds the order $2^m$ of $b$ and multiplies
 *   $x$ by a power of $g = z^s$ ($z$ any non-residue) that
 *   cancels the top factor of $b$, so the order drops.
 * Time: $O(log^2 p)$
 */
#pragma once
#include "millerrabin.h"
ll sqrtMod(ll a, ll p) {
  if ((a %= p) < 0) a += p;
  if (a < 2 || p == 2) return a;
  if (powm(a, (p - 1) / 2, p) != 1) return -1;
  ll s = p - 1, e = 0, z = 2;
  while (s % 2 == 0) s /= 2, ++e;
  while (powm(z, (p - 1) / 2, p) == 1) ++z;
  ull x = powm(a, (s + 1) / 2, p), b = powm(a, s, p),
      g = powm(z, s, p);
  while (b != 1) {
    int m = 0;
    for (ull t = b; t != 1; t = mulm(t, t, p)) ++m;
    ull h = powm(g, 1ULL << (e - m - 1), p);
    g = mulm(h, h, p), x = mulm(x, h, p);
    b = mulm(b, g, p), e = m;
  }
  return x;
}
