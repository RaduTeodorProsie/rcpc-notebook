/**
 * Name: Prefix function
 * Description: `pi[i]` is the largest $k <= i$ such that the first
 *   $k$ characters of $s$ equal the $k$ characters ending at
 *   position $i$: $s[0..k) = s[i-k+1..i]$. E.g. `aabaa` gives
 *   $0, 1, 0, 1, 2$. `match` returns all start positions of `pat`
 *   in $s$: in `pat + '\0' + s`, a value $|"pat"|$ marks the end of
 *   an occurrence (the `\0` stops borders from crossing over).
 * Time: $O(n + m)$
 */
#pragma once
vi pi(const string& s) {
  vi p(sz(s));
  rep(i, 1, sz(s)) {
    int k = p[i - 1];
    while (k && s[i] != s[k]) k = p[k - 1];
    p[i] = k + (s[i] == s[k]);
  }
  return p;
}
vi match(const string& s, const string& pat) {
  vi p = pi(pat + '\0' + s), res;
  rep(i, sz(p) - sz(s), sz(p))
    if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
  return res;
}
// --- uses ---
// Smallest p with s[i] = s[i+p] for all i; s is a power of
// a shorter string iff p < n and p divides n.
int period(const string& s) {
  return s.empty() ? 0 : sz(s) - pi(s).back();
}
