/**
 * Name: Numerical integration
 * Description: `integrate(a, b, f)` is $integral_a^b f(x) d x$
 *   by adaptive Simpson: Simpson's rule fits a parabola through
 *   $f$ at both ends and the middle; split the interval in two
 *   until the halves agree with the whole to within
 *   $15 dot e p s$ (then the error is about $e p s$). It always
 *   splits at least 6 times, so a narrow peak is not missed. At
 *   a kink or a jump (area of a union of circles, a piecewise
 *   function) it is much faster and more precise to call it on
 *   each smooth piece and add.
 * Usage: integrate(0, 1, [](double x) { return x * x; });
 * Time: 2 calls of $f$ per split, at least $129$
 */
#pragma once
// [a, b] with f at a, mid, b known; s: Simpson on [a, b]
template <class F>
double asr(F& f, double a, double b, double fa, double fm,
           double fb, double s, double eps, int d) {
  double m = (a + b) / 2, fl = f((a + m) / 2),
         fr = f((m + b) / 2);
  double L = (m - a) / 6 * (fa + 4 * fl + fm),
         R = (b - m) / 6 * (fm + 4 * fr + fb);
  if (d > 40 || (d > 5 && fabs(L + R - s) <= 15 * eps))
    return L + R + (L + R - s) / 15;
  return asr(f, a, m, fa, fl, fm, L, eps / 2, d + 1) +
         asr(f, m, b, fm, fr, fb, R, eps / 2, d + 1);
}
template <class F>
double integrate(double a, double b, F f,
                 double eps = 1e-9) {
  double fa = f(a), fm = f((a + b) / 2), fb = f(b);
  return asr(f, a, b, fa, fm, fb,
             (b - a) / 6 * (fa + 4 * fm + fb), eps, 0);
}
// --- uses ---
// Double integral over a <= x <= b, lo(x) <= y <= hi(x).
template <class F, class G, class H>
double integrate2(double a, double b, G lo, H hi, F f) {
  return integrate(a, b, [&](double x) {
    return integrate(lo(x), hi(x),
                     [&](double y) { return f(x, y); });
  });
}
