/**
 * Name: HLD path in order
 * Description: For an `op` that is not commutative (matrix
 *   product, max subarray sum, ...): calls `f(l, r, rev)` on
 *   ranges $[l, r)$ of positions in the order they appear on the
 *   path from $a$ to $b$, both ends included. `rev` means the path
 *   walks the range from $r - 1$ down to $l$ (on the way up from
 *   $a$), else from $l$ to $r - 1$. So the segment tree must also
 *   answer a range read backwards: keep both directions per node.
 * Time: $O(log n)$ ranges
 */
#pragma once
#include "hld.h"
template <class F>
void pathInOrder(HLD& h, int a, int b, F f) {
  vector<pii> down; // a's side comes in order: emit at once
  while (h.head[a] != h.head[b])
    if (h.pos[h.head[a]] > h.pos[h.head[b]]) {
      f(h.pos[h.head[a]], h.pos[a] + 1, true);
      a = h.par[h.head[a]];
    } else {
      down.push_back({h.pos[h.head[b]], h.pos[b] + 1});
      b = h.par[h.head[b]];
    }
  if (h.pos[a] >= h.pos[b]) f(h.pos[b], h.pos[a] + 1, true);
  else down.push_back({h.pos[a], h.pos[b] + 1});
  for (int i = sz(down); i--;)
    f(down[i].first, down[i].second, false);
}
