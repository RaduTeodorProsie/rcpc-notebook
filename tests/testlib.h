// Helpers for tests: seeded randomness, generators, and CHECK.
#pragma once

inline mt19937_64 trng(20261105);
inline ll rnd(ll lo, ll hi) {  // uniform in [lo, hi]
  return uniform_int_distribution<ll>(lo, hi)(trng);
}
inline double rndd(double lo, double hi) {
  return uniform_real_distribution<double>(lo, hi)(trng);
}
inline string rstr(int n, char lo = 'a', char hi = 'b') {
  string s(n, lo);
  for (auto& c : s) c = char(rnd(lo, hi));
  return s;
}
inline vector<ll> rvec(int n, ll lo, ll hi) {
  vector<ll> v(n);
  for (auto& x : v) x = rnd(lo, hi);
  return v;
}
// Random tree on n vertices as an adjacency list (parent of i is < i,
// then relabelled randomly).
inline vector<vi> rtree(int n, vector<pii>* edges = nullptr) {
  vi perm(n);
  iota(all(perm), 0);
  shuffle(all(perm), trng);
  vector<vi> g(n);
  rep(i, 1, n) {
    int p = (int)rnd(max(0, i - 3 - (int)rnd(0, n)), i - 1);
    int a = perm[i], b = perm[p];
    g[a].push_back(b), g[b].push_back(a);
    if (edges) edges->push_back({a, b});
  }
  return g;
}
inline vector<pii> rgraph(int n, int m, bool loops = false) {
  vector<pii> e;
  if (n == 1 && !loops) return e;
  while (sz(e) < m) {
    int a = (int)rnd(0, n - 1), b = (int)rnd(0, n - 1);
    if (a != b || loops) e.push_back({a, b});
  }
  return e;
}

#define CHECK(cond, ...)                                          \
  do {                                                            \
    if (!(cond)) {                                                \
      fprintf(stderr, "%s:%d: CHECK(%s) failed. ", __FILE__,      \
              __LINE__, #cond);                                   \
      fprintf(stderr, "" __VA_ARGS__);                            \
      fprintf(stderr, "\n");                                      \
      exit(1);                                                    \
    }                                                             \
  } while (0)
