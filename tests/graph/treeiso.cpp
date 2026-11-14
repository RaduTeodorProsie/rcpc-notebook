#include "graph/treeiso.h"
#include "testlib.h"
// Canonical bracket string of the tree rooted at v (AHU).
string canon(const vector<vi>& g, int v, int p) {
  vector<string> ch;
  for (int u : g[v]) if (u != p) ch.push_back(canon(g, u, v));
  sort(all(ch));
  string s = "(";
  for (auto& c : ch) s += c;
  return s + ")";
}
// Unrooted: the smallest canonical string over all roots.
string canonFree(const vector<vi>& g) {
  string best = canon(g, 0, -1);
  rep(r, 1, sz(g)) best = min(best, canon(g, r, -1));
  return best;
}
vector<vi> relabel(const vector<vi>& g) {
  int n = sz(g);
  vi perm(n);
  iota(all(perm), 0);
  shuffle(all(perm), trng);
  vector<vi> h(n);
  rep(v, 0, n) for (int u : g[v]) h[perm[v]].push_back(perm[u]);
  for (auto& a : h) shuffle(all(a), trng);
  return h;
}
int main() {
  map<string, int> rooted, freeTree;  // canonical string -> class seen
  map<int, string> rootedBack, freeBack;
  auto same = [](map<string, int>& fwd, map<int, string>& back, const string& key, int c) {
    auto [it, fresh] = fwd.try_emplace(key, c);
    auto [jt, fresh2] = back.try_emplace(c, key);
    return it->second == c && jt->second == key;
  };
  rep(it, 0, 6000) {
    int n = rnd(1, it % 3 ? 9 : 30);
    auto g = rtree(n);
    int r = rnd(0, n - 1);
    CHECK(same(rooted, rootedBack, canon(g, r, -1), rootedClass(g, r)), "rooted n=%d", n);
    CHECK(same(freeTree, freeBack, canonFree(g), treeClass(g)), "free n=%d", n);
    auto h = relabel(g);
    CHECK(treeClass(h) == treeClass(g));
    // every subtree: same class iff same canonical string, also across trees
    rep(v, 0, n) for (int u : g[v]) {
      CHECK(same(rooted, rootedBack, canon(g, u, v), rootedClass(g, u, v)));
    }
  }
  // paths (two centroids when n is even) and stars
  rep(n, 1, 40) {
    vector<vi> path(n), star(n);
    rep(i, 1, n) path[i].push_back(i - 1), path[i - 1].push_back(i);
    rep(i, 1, n) star[0].push_back(i), star[i].push_back(0);
    CHECK(treeClass(path) == treeClass(relabel(path)));
    CHECK(treeClass(star) == treeClass(relabel(star)));
    CHECK((treeClass(path) == treeClass(star)) == (n <= 3));
  }
  CHECK(sz(freeTree) > 200);
}
