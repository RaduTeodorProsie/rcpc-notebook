/**
 * Name: Point
 * Description: 2D point/vector. Use `ll` for integer input so
 *   that everything stays exact; `double` for the rest.
 *   `cross(a, b)` $> 0$ iff `a`, `b` turn counter-clockwise
 *   around this point.
 */
#pragma once
template <class T> struct P {
  T x, y;
  P operator+(P o) const { return {x + o.x, y + o.y}; }
  P operator-(P o) const { return {x - o.x, y - o.y}; }
  P operator*(T d) const { return {x * d, y * d}; }
  T dot(P o) const { return x * o.x + y * o.y; }
  T cross(P o) const { return x * o.y - y * o.x; }
  T cross(P a, P b) const {
    return (a - *this).cross(b - *this);
  }
  bool operator<(P o) const {
    return tie(x, y) < tie(o.x, o.y);
  }
  bool operator==(P o) const {
    return x == o.x && y == o.y;
  }
  T dist2() const { return dot(*this); }
  double len() const { return sqrt((double)dist2()); }
  P perp() const { return {-y, x}; } // rotated +90 degrees
  P<double> rot(double a) const {
    double c = cos(a), s = sin(a);
    return {x * c - y * s, x * s + y * c};
  }
};
template <class T> int sgn(T x) {
  return (x > 0) - (x < 0);
}
using Pd = P<double>;
