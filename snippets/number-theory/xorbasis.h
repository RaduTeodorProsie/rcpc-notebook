/**
 * Name: XOR basis
 * Description: Basis of 64-bit vectors over GF(2). `add` returns
 *   false if $x$ was already representable; `best(x)` is the
 *   maximum of $x$ xor a subset.
 * Time: $O(64)$ per operation
 */
#pragma once
struct XorBasis {
  unsigned long long b[64] = {};
  bool add(unsigned long long x) {
    for (int i = 63; i >= 0; --i)
      if (x >> i & 1) {
        if (!b[i]) return b[i] = x, true;
        x ^= b[i];
      }
    return false;
  }
  unsigned long long best(unsigned long long x = 0) {
    for (int i = 63; i >= 0; --i) x = max(x, x ^ b[i]);
    return x;
  }
};
