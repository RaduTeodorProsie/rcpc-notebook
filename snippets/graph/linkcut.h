/**
 * Name: Link-cut tree
 * Description: A forest on vertices $0..n-1$ under `link`
 *   (add an edge between two trees) and `cut` (remove an edge),
 *   with path queries and path updates between any two vertices
 *   of a tree: here sum of vertex values, and add $x$ to every
 *   vertex on a path. `lca(u, v, r)` is the LCA with the tree
 *   rooted at $r$. How it works: every tree is cut into vertical
 *   paths, each kept as a splay tree ordered by depth.
 *   `access(v)` makes the root to $v$ path one splay tree with
 *   $v$ at its top; `reroot(v)` then reverses that path (lazily),
 *   so $v$ becomes the root. A query on $u..v$: reroot at $u$,
 *   access $v$, read $v$'s aggregate. Other aggregates: change
 *   `N`, `apply`, `pull`. Max with ties, min, gcd work the same;
 *   for an order-dependent one (e.g. hash of the path) keep it
 *   for both directions and swap them on reversal. Edge values:
 *   make each edge a vertex of its own, linked to both ends.
 *   Not for subtree queries.
 * Usage: LCT t(n); t.link(0, 1); t.update(1, 1, 7); // a_1 += 7
 *   t.query(0, 1); t.cut(0, 1); // u, v must be connected
 * Time: $O(log n)$ amortized
 */
#pragma once
struct LCT {
  struct N {
    int c[2]{}, p = 0, sz = 1;
    ll val = 0, sum = 0, add = 0;
    bool rev = 0;
  };
  vector<N> t; // node 0 is null, vertex v is node v + 1
  LCT(int n) : t(n + 1) { t[0].sz = 0; }
  bool isRoot(int x) {
    N& p = t[t[x].p];
    return p.c[0] != x && p.c[1] != x;
  }
  void apply(int x, ll a, bool r) {
    if (!x) return;
    N& n = t[x];
    n.val += a, n.sum += a * n.sz, n.add += a;
    if (r) swap(n.c[0], n.c[1]), n.rev ^= 1;
  }
  void push(int x) {
    for (int c : t[x].c) apply(c, t[x].add, t[x].rev);
    t[x].add = 0, t[x].rev = 0;
  }
  void pull(int x) {
    N &n = t[x], &l = t[n.c[0]], &r = t[n.c[1]];
    n.sz = 1 + l.sz + r.sz, n.sum = n.val + l.sum + r.sum;
  }

  void rot(int x) {
    int p = t[x].p, g = t[p].p, d = t[p].c[1] == x;
    int b = t[x].c[!d];
    if (!isRoot(p)) t[g].c[t[g].c[1] == p] = x;
    t[x].p = g, t[x].c[!d] = p, t[p].p = x;
    t[p].c[d] = b;
    if (b) t[b].p = p;
    pull(p), pull(x);
  }
  void splay(int x) {
    vi st{x};
    for (int y = x; !isRoot(y); y = t[y].p)
      st.push_back(t[y].p);
    for (; sz(st); st.pop_back()) push(st.back());
    while (!isRoot(x)) {
      int p = t[x].p, g = t[p].p;
      if (!isRoot(p))
        rot((t[g].c[1] == p) == (t[p].c[1] == x) ? p : x);
      rot(x);
    }
  }
  int access(int x) { // returns the last path top met
    int last = 0;
    for (int y = x; y; last = y, y = t[y].p)
      splay(y), t[y].c[1] = last, pull(y);
    splay(x);
    return last;
  }
  void reroot(int x) { access(x), apply(x, 0, 1); }
  int root(int x) {
    access(x);
    while (t[x].c[0]) push(x), x = t[x].c[0];
    splay(x);
    return x;
  }

  bool connected(int u, int v) {
    return root(u + 1) == root(v + 1);
  }
  void link(int u, int v) { // u, v in different trees
    reroot(u + 1), t[u + 1].p = v + 1;
  }
  void cut(int u, int v) { // the edge u-v must exist
    reroot(u + 1), access(v + 1);
    t[v + 1].c[0] = t[u + 1].p = 0, pull(v + 1);
  }
  ll query(int u, int v) {
    reroot(u + 1), access(v + 1);
    return t[v + 1].sum;
  }
  void update(int u, int v, ll a) {
    reroot(u + 1), access(v + 1), apply(v + 1, a, 0);
  }
  int lca(int u, int v, int r) {
    reroot(r + 1), access(u + 1);
    return access(v + 1) - 1;
  }
};
