/**
 * Name: Lazy segment tree variants
 * Description: Each block replaces the marked block of the lazy
 *   segment tree. Leaves: `T{v, v, 1}`, `T{v, 1}`, `T{v, 1}`.
 */
// == range assign; sum and minimum ==
struct T { ll sum = 0, mn = LLONG_MAX; int len = 0; };
using U = ll;
U none = LLONG_MIN;
T op(T a, T b) {
  return {a.sum + b.sum, min(a.mn, b.mn), a.len + b.len};
}
void apply(T& a, U f) {
  if (f != none) a.sum = f * a.len, a.mn = f;
}
U comp(U f, U g) { return f != none ? f : g; }
// == x -> b x + c (mod P); sum ==
// Each element x becomes b x + c, so a sum of len elements
// becomes b sum + c len. comp(f, g) is f after g:
// bf (bg x + cg) + cf = (bf bg) x + (bf cg + cf).
// Assign v is
// (0, v), add v is (1, v), multiply by v is (v, 0); none is
// (1, 0), the map x -> x.
static constexpr ll P = 998244353;
struct T { ll sum = 0; int len = 0; };
using U = pair<ll, ll>; // (b, c)
U none = {1, 0};
T op(T a, T b) {
  return {(a.sum + b.sum) % P, a.len + b.len};
}
void apply(T& a, U f) {
  a.sum = (f.first * a.sum + f.second * a.len) % P;
}
U comp(U f, U g) {
  return {f.first * g.first % P,
          (f.first * g.second + f.second) % P};
}
// == range add; maximum and how many times it occurs ==
struct T { ll mx = LLONG_MIN; int cnt = 0; };
using U = ll;
U none = 0;
T op(T a, T b) {
  if (a.mx != b.mx) return a.mx > b.mx ? a : b;
  return {a.mx, a.cnt + b.cnt};
}
void apply(T& a, U f) {
  if (a.cnt) a.mx += f;
}
U comp(U f, U g) { return f + g; }
