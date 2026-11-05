/**
 * Name: Union-find
 * Description: Disjoint sets with union by size and path
 *   compression. `join` returns false if already joined.
 * Time: $O(alpha(n))$ amortized
 */
#pragma once
struct DSU {
  vi p;
  DSU(int n) : p(n, -1) {}
  int find(int x) {
    return p[x] < 0 ? x : p[x] = find(p[x]);
  }
  int size(int x) { return -p[find(x)]; }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (p[a] > p[b]) swap(a, b);
    p[a] += p[b], p[b] = a;
    return true;
  }
};
