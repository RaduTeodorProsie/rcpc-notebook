/**
 * Name: Longest increasing subsequence
 * Description: Indices of a longest strictly increasing
 *   subsequence. For non-decreasing, use `upper_bound`.
 * Time: $O(n log n)$
 */
#pragma once
vi lis(const vector<ll>& a) {
  vi d, par(sz(a), -1); // d[k]: end of a best (k+1)-run
  rep(i, 0, sz(a)) {
    auto it = lower_bound(all(d), a[i],
        [&](int j, ll v) { return a[j] < v; });
    par[i] = it == d.begin() ? -1 : *prev(it);
    if (it == d.end()) d.push_back(i);
    else *it = i;
  }
  vi res;
  int i = d.empty() ? -1 : d.back();
  for (; i >= 0; i = par[i]) res.push_back(i);
  reverse(all(res));
  return res;
}
