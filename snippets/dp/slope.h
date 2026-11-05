/**
 * Name: Slope trick
 * Description: A convex piecewise linear $f$ with integer
 *   breakpoints, stored as `mn` $= min f$ plus the breakpoints
 *   left of the minimum (max-heap `L`) and right of it (min-heap
 *   `R`); at each one the slope changes by 1. Every operation
 *   below keeps $f$ convex. Start: $f equiv 0$ is the empty
 *   structure. "$0$ at $a$, $infinity$ elsewhere": push $a$ into
 *   both heaps $K$ times, $K$ more than any slope reached later.
 *   The minimum is reached on $[$`topL()`$,$ `topR()`$]$. Concave
 *   $f$: store $-f$. Example: min $sum |a_i - b_i|$ over
 *   non-decreasing $b$ is `addAbs(a_i)`, `prefixMin()` for each $i$.
 * Time: $O(log n)$ per operation
 */
#pragma once
struct Slope {
  static constexpr ll BIG = LLONG_MAX / 4;
  ll mn = 0, addL = 0, addR = 0; // lazy shifts of L and R
  priority_queue<ll> L;
  priority_queue<ll, vector<ll>, greater<>> R;
  ll topL() { return sz(L) ? L.top() + addL : -BIG; }
  ll topR() { return sz(R) ? R.top() + addR : BIG; }
  void pushL(ll a) { L.push(a - addL); }
  void pushR(ll a) { R.push(a - addR); }
  void addConst(ll c) { mn += c; }
  void addRight(ll a) { // f += max(0, x - a)
    mn += max(0LL, topL() - a);
    pushL(a), pushR(topL()), L.pop();
  }
  void addLeft(ll a) { // f += max(0, a - x)
    mn += max(0LL, a - topR());
    pushR(a), pushL(topR()), R.pop();
  }
  void addAbs(ll a) { addRight(a), addLeft(a); }
  void prefixMin() { R = {}; } // f(x) = min over y <= x
  void suffixMin() { L = {}; } // f(x) = min over y >= x
  void shift(ll a) { addL += a, addR += a; } // f(x - a)
  // f(x) = min of f(y) over x - b <= y <= x - a  (a <= b)
  void window(ll a, ll b) { addL += a, addR += b; }
  ll eval(ll x) { // empties the heaps: call on a copy
    ll r = mn;
    for (; sz(L); L.pop()) r += max(0LL, topL() - x);
    for (; sz(R); R.pop()) r += max(0LL, x - topR());
    return r;
  }
};
