/**
 * Name: Kinetic segment tree
 * Description: Position $i$ holds a value $b_i$ and a speed $a_i$.
 *   `heat(l, r, d)`, $d >= 0$: every $i$ in $[l, r)$ moves forward
 *   $d$ units of time, $b_i += a_i d$. `query(l, r)`: max $b_i$.
 *   `set(i, a, b)`. So it is max over lines $a_i t + b_i$ where
 *   each position has its own clock $t$; e.g. DP transitions
 *   $max_j (a_j x + b_j)$ where $x$ grows on ranges of $j$. Each node
 *   stores its winning line and `melt`, the time until some
 *   winner in its subtree changes (a faster line catches up). A
 *   heat shorter than `melt` just shifts the node; a longer one
 *   recomputes it from the children. Min: negate $a$ and $b$.
 *   Empty positions: $(0, -10^18)$. Keep values within $10^18$.
 * Time: $O(log^2 n)$ amortized `heat`, $O(log n)$ others
 */
#pragma once
struct KST {
  struct Ln { ll a, b; };
  const ll INF = LLONG_MAX / 2;
  int n;
  vector<Ln> t;
  vector<ll> melt, lz;
  KST(const vector<Ln>& v)
      : n(sz(v)), t(4 * n), melt(4 * n, INF), lz(4 * n) {
    if (n) build(1, 0, n, v);
  }
  void build(int x, int l, int r, const vector<Ln>& v) {
    if (r - l == 1) return void(t[x] = v[l]);
    int m = (l + r) / 2;
    build(2 * x, l, m, v), build(2 * x + 1, m, r, v);
    pull(x);
  }
  void pull(int x) {
    Ln p = t[2 * x], q = t[2 * x + 1];
    if (p.b < q.b || (p.b == q.b && p.a < q.a)) swap(p, q);
    t[x] = p, melt[x] = min(melt[2 * x], melt[2 * x + 1]);
    if (q.a > p.a) // q catches up after ceil(gap / speed)
      melt[x] = min(melt[x], (p.b - q.b + q.a - p.a - 1) /
                                 (q.a - p.a));
  }
  void adv(int x, ll d) { // whole subtree of x
    t[x].b += t[x].a * d, lz[x] += d;
    if (melt[x] == INF) return; // never changes
    if ((melt[x] -= d) <= 0) push(x), pull(x);
  }
  void push(int x) {
    if (lz[x]) adv(2 * x, lz[x]), adv(2 * x + 1, lz[x]);
    lz[x] = 0;
  }
  void heat(int l, int r, ll d) { upd(l, r, d, 1, 0, n); }
  void upd(int l, int r, ll d, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return;
    if (l <= lo && hi <= r) return adv(x, d);
    push(x);
    int m = (lo + hi) / 2;
    upd(l, r, d, 2 * x, lo, m);
    upd(l, r, d, 2 * x + 1, m, hi);
    pull(x);
  }
  void set(int i, Ln f) { put(i, f, 1, 0, n); }
  void put(int i, Ln f, int x, int lo, int hi) {
    if (hi - lo == 1) return void(t[x] = f);
    push(x);
    int m = (lo + hi) / 2;
    if (i < m) put(i, f, 2 * x, lo, m);
    else put(i, f, 2 * x + 1, m, hi);
    pull(x);
  }
  ll query(int l, int r) { return qry(l, r, 1, 0, n); }
  ll qry(int l, int r, int x, int lo, int hi) {
    if (r <= lo || hi <= l) return -INF;
    if (l <= lo && hi <= r) return t[x].b;
    push(x);
    int m = (lo + hi) / 2;
    return max(qry(l, r, 2 * x, lo, m),
               qry(l, r, 2 * x + 1, m, hi));
  }
};
