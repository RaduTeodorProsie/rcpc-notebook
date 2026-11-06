/**
 * Name: 3D convex hull
 * Description: Faces of the convex hull as triangles $(a, b, c)$
 *   of indices, counter-clockwise seen from outside; `q` is an
 *   outward normal. Needs $>= 4$ points and *no four coplanar*
 *   (else faces go missing). Integer input with coplanar points:
 *   use `P3<double>` and add `rand() * 1e-6 / RAND_MAX` to every
 *   coordinate; flat faces then come out as several thin
 *   triangles, and area and volume are fine. With `ll` it is
 *   exact for $|x|, |y|, |z| <= 5 dot 10^5$.
 * Time: $O(n^2)$
 */
#pragma once
#include "point3.h"
template <class T> struct Hull3 {
  using Q = P3<T>;
  struct F { Q q; int a, b, c; bool fl; };
  struct PR { // the two faces' third vertices at an edge
    int a = -1, b = -1;
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
  };
  vector<F> fs;
  Hull3(const vector<Q>& A) {
    int n = sz(A);
    vector<vector<PR>> E(n, vector<PR>(n));
    auto mf = [&](int i, int j, int k, int l) {
      Q q = (A[j] - A[i]).cross(A[k] - A[i]);
      bool fl = q.dot(A[l]) > q.dot(A[i]);
      if (fl) q = q * -1;
      E[i][j].ins(k), E[i][k].ins(j), E[j][k].ins(i);
      fs.push_back({q, i, j, k, fl});
    };
    rep(i, 0, 4) rep(j, i + 1, 4) rep(k, j + 1, 4)
      mf(i, j, k, 6 - i - j - k);
    rep(i, 4, n) {
      rep(j, 0, sz(fs)) {
        F f = fs[j];
        if (f.q.dot(A[i]) > f.q.dot(A[f.a])) { // visible
          E[f.a][f.b].rem(f.c), E[f.a][f.c].rem(f.b);
          E[f.b][f.c].rem(f.a);
          swap(fs[j--], fs.back()), fs.pop_back();
        }
      }
      int m = sz(fs);
      rep(j, 0, m) { // edges on the horizon get a new face
        F f = fs[j];
        if (E[f.a][f.b].cnt() != 2) mf(f.a, f.b, i, f.c);
        if (E[f.a][f.c].cnt() != 2) mf(f.a, f.c, i, f.b);
        if (E[f.b][f.c].cnt() != 2) mf(f.b, f.c, i, f.a);
      }
    }
    for (F& f : fs)
      if (f.fl) swap(f.b, f.c);
  }
};
