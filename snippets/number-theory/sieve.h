/**
 * Name: Linear sieve
 * Description: Primes up to $n$, smallest prime factor `lp`, and
 *   $phi$, $mu$. The marked lines define a multiplicative
 *   function: at $p$, at $i p$ with $p | i$, and with $p divides.not i$.
 * Time: $O(n)$
 */
#pragma once
struct Sieve {
  vi lp, pr, phi, mu;
  Sieve(int n) : lp(n + 1), phi(n + 1), mu(n + 1) {
    phi[1] = mu[1] = 1;
    rep(i, 2, n + 1) {
      if (!lp[i]) {
        lp[i] = i, pr.push_back(i);
        phi[i] = i - 1, mu[i] = -1; //!
      }
      for (int p : pr) {
        if (p > lp[i] || (ll)i * p > n) break;
        lp[i * p] = p;
        if (p == lp[i]) {
          phi[i * p] = phi[i] * p, mu[i * p] = 0; //!
        } else {
          phi[i * p] = phi[i] * (p - 1), mu[i * p] = -mu[i]; //!
        }
      }
    }
  }
  vector<pii> factor(int x) { // (prime, exponent), x <= n
    vector<pii> f;
    while (x > 1) {
      int p = lp[x], e = 0;
      while (x % p == 0) x /= p, ++e;
      f.push_back({p, e});
    }
    return f;
  }
};
