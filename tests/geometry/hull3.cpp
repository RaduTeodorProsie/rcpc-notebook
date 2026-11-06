#include "geometry/hull3.h"
#include "testlib.h"
template <class T> bool same(P3<T> a, P3<T> b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
bool anyCoplanar4(const vector<P3<ll>>& a) {
  int n = sz(a);
  rep(i, 0, n) rep(j, i + 1, n) rep(k, j + 1, n) {
    auto c = (a[j] - a[i]).cross(a[k] - a[i]);
    rep(l, k + 1, n) if (c.dot(a[l] - a[i]) == 0) return true;
  }
  return false;
}
// Checks that the faces form a closed, consistently oriented surface whose
// every face plane has all points on its inner side (up to eps), with every
// extreme point used: then it is the hull. Returns the volume.
template <class T> double check(const vector<P3<T>>& A, int it, double eps = 0) {
  Hull3<T> h(A);
  int n = sz(A);
  map<pii, int> dir;
  set<int> verts;
  for (auto& f : h.fs) {
    CHECK(f.a != f.b && f.b != f.c && f.a != f.c, "it=%d", it);
    auto c = (A[f.b] - A[f.a]).cross(A[f.c] - A[f.a]);
    if (eps == 0) CHECK(same(c, f.q), "it=%d normal", it);
    else CHECK(c.dot(f.q) > 0, "it=%d orientation", it);
    CHECK(c.x || c.y || c.z, "it=%d degenerate face", it);
    double len = sqrt((double)f.q.x * f.q.x + (double)f.q.y * f.q.y + (double)f.q.z * f.q.z);
    rep(i, 0, n) CHECK(f.q.dot(A[i] - A[f.a]) <= eps * len, "it=%d point %d outside by %g", it, i, (double)(f.q.dot(A[i] - A[f.a]) / len));
    for (auto [x, y] : {pii{f.a, f.b}, pii{f.b, f.c}, pii{f.c, f.a}}) dir[{x, y}]++;
    verts.insert(f.a), verts.insert(f.b), verts.insert(f.c);
  }
  for (auto [e, k] : dir) {
    CHECK(k == 1, "it=%d edge used %d times", it, k);
    CHECK(dir.count({e.second, e.first}), "it=%d open edge", it);
  }
  rep(k, 0, 100) {  // the unique maximum in a random direction is a vertex
    P3<T> d{(T)rnd(-1000, 1000), (T)rnd(-1000, 1000), (T)rnd(-1000, 1000)};
    vi top;
    rep(i, 0, n) {
      if (top.empty() || d.dot(A[i]) > d.dot(A[top[0]])) top = {i};
      else if (d.dot(A[i]) == d.dot(A[top[0]])) top.push_back(i);
    }
    if (sz(top) == 1) CHECK(verts.count(top[0]), "it=%d extreme point %d missing", it, top[0]);
  }
  vector<array<P3<T>, 3>> tri;
  for (auto& f : h.fs) tri.push_back({A[f.a], A[f.b], A[f.c]});
  double v = volume(tri);
  CHECK(v > 0, "it=%d", it);
  return v;
}
vector<P3<double>> perturb(const vector<P3<ll>>& A) {
  vector<P3<double>> B;
  for (auto p : A)
    B.push_back({p.x + rand() * 1e-6 / RAND_MAX, p.y + rand() * 1e-6 / RAND_MAX,
                 p.z + rand() * 1e-6 / RAND_MAX});
  return B;
}
int main() {
  srand(7);
  rep(it, 0, 1500) {  // exact ll, no four coplanar, up to the stated bound
    int n = rnd(4, it < 1000 ? 10 : 35);
    ll C = it % 2 ? 50 : 500000;
    vector<P3<ll>> A(n);
    do for (auto& p : A) p = {rnd(-C, C), rnd(-C, C), rnd(-C, C)};
    while (anyCoplanar4(A));
    double v = check(A, it);
    CHECK(fabs(check(perturb(A), it, 1e-7) - v) <= 1e-3 * max(1.0, v), "it=%d", it);
  }
  rep(it, 0, 3000) {  // tiny integer coordinates, perturbed doubles
    int n = rnd(4, it < 2000 ? 12 : 60);
    ll C = it % 2 ? 2 : 6;
    vector<P3<ll>> A(n);
    for (auto& p : A) p = {rnd(-C, C), rnd(-C, C), rnd(-C, C)};
    check(perturb(A), 10000 + it, 1e-7);
  }
  rep(it, 0, 200) {  // box corners plus lattice points inside: known volume
    ll X = rnd(1, 5), Y = rnd(1, 5), Z = rnd(1, 5);
    vector<P3<ll>> A;
    rep(x, 0, 2) rep(y, 0, 2) rep(z, 0, 2) A.push_back({x * X, y * Y, z * Z});
    rep(k, 0, rnd(0, 60)) A.push_back({rnd(0, X), rnd(0, Y), rnd(0, Z)});
    shuffle(all(A), trng);
    double v = check(perturb(A), 20000 + it, 1e-7);
    CHECK(fabs(v - X * Y * Z) < 1e-3, "it=%d vol %f want %lld", it, v, X * Y * Z);
  }
  {  // doubles on a sphere: 2n - 4 faces, area just below 4 pi
    vector<P3<double>> A;
    rep(i, 0, 300) {
      double z = rndd(-1, 1), t = rndd(0, 2 * M_PI), r = sqrt(1 - z * z);
      A.push_back({r * cos(t), r * sin(t), z});
    }
    Hull3<double> h(A);
    double area = 0;
    for (auto& f : h.fs) area += (A[f.b] - A[f.a]).cross(A[f.c] - A[f.a]).len() / 2;
    CHECK(sz(h.fs) == 2 * 300 - 4, "faces %d", sz(h.fs));
    CHECK(area > 4 * M_PI * 0.97 && area < 4 * M_PI, "area %f", area);
  }
}
