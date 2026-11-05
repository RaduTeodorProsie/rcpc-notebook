/**
 * Name: General matching
 * Description: Edmonds' blossom algorithm for maximum matching
 *   in any undirected graph; `match[v]` is the partner or $-1$.
 * Time: $O(V^3)$
 */
#pragma once
struct Blossom {
  int n;
  vector<vi> g;
  vi match, p, base, q;
  vector<bool> used, blos;
  Blossom(int n)
      : n(n), g(n), match(n, -1), p(n), base(n) {}
  void addEdge(int a, int b) {
    g[a].push_back(b), g[b].push_back(a);
  }
  int lca(int a, int b) {
    vector<bool> seen(n);
    for (;;) {
      a = base[a], seen[a] = true;
      if (match[a] < 0) break;
      a = p[match[a]];
    }
    for (;; b = p[match[b]])
      if (seen[b = base[b]]) return b;
  }
  void mark(int v, int b, int child) {
    for (; base[v] != b; v = p[match[v]]) {
      blos[base[v]] = blos[base[match[v]]] = true;
      p[v] = child, child = match[v];
    }
  }
  int augment(int root) {
    used.assign(n, false), p.assign(n, -1);
    iota(all(base), 0);
    used[root] = true, q = {root};
    rep(h, 0, sz(q)) {
      int v = q[h];
      for (int to : g[v]) {
        if (base[v] == base[to] || match[v] == to) continue;
        int mt = match[to];
        if (to == root || (mt >= 0 && p[mt] >= 0)) {
          int c = lca(v, to);
          blos.assign(n, false);
          mark(v, c, to), mark(to, c, v);
          rep(i, 0, n) if (blos[base[i]]) {
            base[i] = c;
            if (!used[i]) used[i] = true, q.push_back(i);
          }
        } else if (p[to] < 0) {
          p[to] = v;
          if (match[to] < 0) return to;
          used[match[to]] = true, q.push_back(match[to]);
        }
      }
    }
    return -1;
  }
  int solve() {
    int res = 0;
    rep(v, 0, n) if (match[v] < 0) {
      int u = augment(v);
      if (u < 0) continue;
      ++res;
      while (u >= 0) {
        int pv = p[u], nx = match[pv];
        match[u] = pv, match[pv] = u, u = nx;
      }
    }
    return res;
  }
};
