/**
 * Name: XOR basis
 * Description: Basis of 64-bit vectors over GF(2); `b[i]` has top
 *   bit $i$. `add` returns false if $x$ was already representable.
 *   `best(x)` / `worst(x)`: max / min of $x$ xor a subset. `has(x)`:
 *   is $x$ a xor of a subset. The span has $2^"rank"$ values; from
 *   $n$ added numbers each value is the xor of $2^(n - "rank")$
 *   subsets (so $0$ from a non-empty one iff $n > "rank"$). `kth(k)`:
 *   $k$-th smallest value of the span, from $0$. It first reduces
 *   the basis (clears bit $i$ from the others when `b[i]` exists);
 *   then the values sorted are the subset xors in binary order.
 * Time: $O(64)$ per operation, `kth` $O(64^2)$
 */
#pragma once
using ull = unsigned long long;
struct XorBasis {
  ull b[64] = {};
  int rank = 0;
  bool add(ull x) {
    for (int i = 63; i >= 0; --i)
      if (x >> i & 1) {
        if (!b[i]) return b[i] = x, ++rank, true;
        x ^= b[i];
      }
    return false;
  }
  ull best(ull x = 0) {
    for (int i = 63; i >= 0; --i) x = max(x, x ^ b[i]);
    return x;
  }
  ull worst(ull x) {
    for (int i = 63; i >= 0; --i) x = min(x, x ^ b[i]);
    return x;
  }
  bool has(ull x) { return !worst(x); }
  ull kth(ull k) { // k < 2^rank
    rep(i, 0, 64) if (b[i]) rep(j, i + 1, 64)
      if (b[j] >> i & 1) b[j] ^= b[i];
    ull r = 0;
    for (int i = 0, j = 0; i < 64; ++i)
      if (b[i] && (k >> j++ & 1)) r ^= b[i];
    return r;
  }
};
// --- uses ---
// Max xor of a subset of a[l..r): add a[0..r) in order,
// keeping per bit the vector with the latest position;
// then use only vectors at positions >= l. Offline: sort
// queries by r. Online: keep a copy per prefix.
struct RangeBasis {
  ull b[64] = {};
  int pos[64] = {};
  void add(ull x, int p) {
    for (int i = 63; i >= 0; --i)
      if (x >> i & 1) {
        if (!b[i]) { b[i] = x, pos[i] = p; return; }
        if (pos[i] < p) swap(pos[i], p), swap(b[i], x);
        x ^= b[i];
      }
  }
  ull best(int l) {
    ull x = 0;
    for (int i = 63; i >= 0; --i)
      if (b[i] && pos[i] >= l) x = max(x, x ^ b[i]);
    return x;
  }
};
