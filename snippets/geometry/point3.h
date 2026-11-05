/**
 * Name: 3D basics
 * Description: `cross` is perpendicular to both, with length the
 *   parallelogram area. Plane through $a, b, c$: normal
 *   $n = (b - a) times (c - a)$; signed distance of $p$:
 *   $n dot (p - a) \/ |n|$, sign = side. Line $p + t d$ meets that plane
 *   at $t = n dot (a - p) \/ (n dot d)$ (parallel if $n dot d = 0$).
 *   Distance from $p$ to line $a + t d$: $|(p - a) times d| \/ |d|$.
 *   Lines $a + t d$, $b + s e$: $|(b - a) dot (d times e)| \/ |d times e|$.
 *   Volume of tetrahedron $a b c d$: $|(b - a) times (c - a) dot
 *   (d - a)| \/ 6$. `volume` of a closed polyhedron given as
 *   triangles, all outward (counter-clockwise seen from outside).
 */
#pragma once
template <class T> struct P3 {
  T x, y, z;
  P3 operator+(P3 o) const {
    return {x + o.x, y + o.y, z + o.z};
  }
  P3 operator-(P3 o) const {
    return {x - o.x, y - o.y, z - o.z};
  }
  P3 operator*(T d) const { return {x * d, y * d, z * d}; }
  T dot(P3 o) const { return x * o.x + y * o.y + z * o.z; }
  P3 cross(P3 o) const {
    return {y * o.z - z * o.y, z * o.x - x * o.z,
            x * o.y - y * o.x};
  }
  T dist2() const { return dot(*this); }
  double len() const { return sqrt((double)dist2()); }
};
template <class T>
double volume(const vector<array<P3<T>, 3>>& faces) {
  T v = 0;
  for (auto& [a, b, c] : faces) v += a.cross(b).dot(c);
  return v / 6.0;
}
