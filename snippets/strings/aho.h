/**
 * Name: Aho-Corasick
 * Description: Automaton over lowercase patterns. After
 *   `build`, `nx` is the full transition table, `cnt[v]` is the
 *   number of patterns ending at state $v$ (as a suffix), and
 *   `ord` lists states in BFS order. For DP over texts that
 *   avoid the patterns, forbid states with `cnt > 0`.
 * Time: $O(26 dot sum |p_i|)$
 */
#pragma once
struct Aho {
  vector<array<int, 26>> nx; //!
  vi link, cnt, ord;
  Aho() : nx(1), link(1), cnt(1) { nx[0].fill(-1); }
  int add(const string& s) { // returns the end state
    int v = 0;
    for (char ch : s) {
      int c = ch - 'a'; //!
      if (nx[v][c] < 0) {
        nx[v][c] = sz(nx);
        nx.emplace_back().fill(-1);
        link.push_back(0), cnt.push_back(0);
      }
      v = nx[v][c];
    }
    cnt[v]++;
    return v;
  }
  void build() {
    queue<int> q;
    for (int& u : nx[0])
      if (u < 0) u = 0;
      else q.push(u);
    while (sz(q)) {
      int v = q.front();
      q.pop(), ord.push_back(v);
      cnt[v] += cnt[link[v]];
      rep(c, 0, 26) { //!
        int& u = nx[v][c];
        if (u < 0) u = nx[link[v]][c];
        else link[u] = nx[link[v]][c], q.push(u);
      }
    }
  }
};
// --- uses ---
ll totalMatches(Aho& a, const string& t) {
  ll r = 0;
  int v = 0;
  for (char c : t) v = a.nx[v][c - 'a'], r += a.cnt[v];
  return r;
}
// h[add(p)] = number of occurrences of pattern p in t.
vector<ll> hits(Aho& a, const string& t) {
  vector<ll> h(sz(a.nx));
  int v = 0;
  for (char c : t) v = a.nx[v][c - 'a'], h[v]++;
  for (int i = sz(a.ord) - 1; i >= 0; --i)
    h[a.link[a.ord[i]]] += h[a.ord[i]];
  return h;
}
