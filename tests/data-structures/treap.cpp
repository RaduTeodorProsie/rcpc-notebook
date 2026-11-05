#include "data-structures/treap.h"
#include "testlib.h"
void collect(Node* t, vector<ll>& out) {
  if (!t) return;
  push(t);
  collect(t->l, out), out.push_back(t->val), collect(t->r, out);
}
int main() {
  rep(it, 0, 200) {
    Node* t = nullptr;
    vector<ll> a;
    rep(q, 0, 300) {
      int op = rnd(0, 3), n = sz(a);
      if (op == 0 || n == 0) {
        int pos = rnd(0, n);
        ll v = rnd(-100, 100);
        t = insert(t, pos, v), a.insert(a.begin() + pos, v);
      } else if (op == 1) {
        int pos = rnd(0, n - 1);
        t = erase(t, pos), a.erase(a.begin() + pos);
      } else {
        int l = rnd(0, n), r = rnd(0, n);
        if (l > r) swap(l, r);
        if (op == 2) t = reverse(t, l, r), reverse(a.begin() + l, a.begin() + r);
        else {
          ll w = accumulate(a.begin() + l, a.begin() + r, 0ll);
          CHECK(rangeSum(t, l, r) == w);
        }
      }
      CHECK(size(t) == sz(a));
    }
    vector<ll> out;
    collect(t, out);
    CHECK(out == a);
  }
}
