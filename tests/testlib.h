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

// Performance: PERF("name", ms) { ... } runs the block once and fails if it
// takes longer than ms milliseconds times $PERF_SCALE (default 1).
struct PerfRun {
  const char* name;
  double ms;
  chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
  bool done = false;
  bool go() { return done ? false : (done = true); }
  ~PerfRun() {
    double el = chrono::duration<double, milli>(chrono::steady_clock::now() - t0).count();
    const char* s = getenv("PERF_SCALE");
    double lim = ms * (s ? atof(s) : 1.0);
    printf("%-46s %8.1f ms  (limit %.0f)\n", name, el, lim);
    fflush(stdout);
    CHECK(el <= lim, "%s took %.1f ms, limit %.0f ms", name, el, lim);
  }
};
#define PERF(name, ms) for (PerfRun perf_run_{name, ms}; perf_run_.go();)
