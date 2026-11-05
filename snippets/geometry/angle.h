/**
 * Name: Angular sort
 * Description: `angleLess` orders vectors by angle in $[0, 2 pi)$,
 *   counter-clockwise from the positive $x$ axis, exactly for
 *   `ll`; equal angles: shorter first. `half` is $0$ for
 *   angles in $[0, pi)$, $1$ for $[pi, 2 pi)$; comparing halves first
 *   makes `cross` valid. Around a point $c$: sort $p - c$. No zero
 *   vectors. Sweeps over all directions: sort once, then go
 *   around twice (index $i mod n$) with two pointers.
 * Usage: sort(all(v), angleLess<ll>);
 */
#pragma once
#include "point.h"
template <class T> bool half(P<T> p) {
  return p.y < 0 || (p.y == 0 && p.x < 0);
}
template <class T> bool angleLess(P<T> a, P<T> b) {
  if (half(a) != half(b)) return half(a) < half(b);
  T c = a.cross(b);
  return c != 0 ? c > 0 : a.dist2() < b.dist2();
}
