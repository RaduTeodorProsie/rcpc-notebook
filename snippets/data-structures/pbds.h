/**
 * Name: Policy-based structures
 * Description: Ordered set: `find_by_order(k)` is the $k$-th
 *   element (0-based), `order_of_key(x)` counts elements $< x$.
 *   Use `less_equal` or pairs for a multiset. `gp_hash_table` is
 *   a fast hash map; the custom hash resists anti-hash tests.
 * Time: $O(log n)$; hash map $O(1)$ expected
 */
#pragma once
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
struct chash {
  size_t operator()(unsigned long long x) const {
    static const unsigned long long K = chrono::
        steady_clock::now().time_since_epoch().count();
    x += K + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};
template <class K, class V>
using hmap = gp_hash_table<K, V, chash>;
