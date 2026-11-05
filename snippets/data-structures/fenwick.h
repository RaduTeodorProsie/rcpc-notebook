/**
 * Name: Fenwick tree
 * Description: Point add, prefix sum over $[0, i)$. `lower(k)`
 *   gives the smallest $i$ with `sum(i+1)` $> k$; needs all
 *   values $>= 0$.
 * Time: $O(log n)$ per operation
 */
#pragma once
struct Fenwick {
  vector<ll> t;
  Fenwick(int n) : t(n + 1) {}
  void add(int i, ll v) {
    for (++i; i < sz(t); i += i & -i) t[i] += v;
  }
  ll sum(int i) {
    ll r = 0;
    for (; i > 0; i -= i & -i) r += t[i];
    return r;
  }
  int lower(ll k) {
    int pos = 0;
    for (int pw = 1 << __lg(sz(t)); pw; pw >>= 1)
      if (pos + pw < sz(t) && t[pos + pw] <= k)
        pos += pw, k -= t[pos];
    return pos;
  }
};
// --- uses ---
// Range add on [l, r), prefix sum on [0, i).
struct RangeFenwick {
  Fenwick a, b;
  RangeFenwick(int n) : a(n + 1), b(n + 1) {}
  void add(int l, int r, ll v) {
    a.add(l, v), a.add(r, -v);
    b.add(l, v * l), b.add(r, -v * r);
  }
  ll sum(int i) { return a.sum(i) * i - b.sum(i); }
};
