/**
 * Name: Implicit treap
 * Description: Sequence with split/merge by position. `push` and
 *   `pull` carry the lazy reverse and the subtree sum; edit them
 *   for other data. Positions are 0-based.
 * Time: $O(log n)$ expected
 */
#pragma once
struct Node {
  Node *l = 0, *r = 0;
  int pri, size = 1;
  ll val, sum; //!
  bool rev = false; //!
  Node(ll v) : pri(rand()), val(v), sum(v) {}
};
int size(Node* t) { return t ? t->size : 0; }
ll sum(Node* t) { return t ? t->sum : 0; }
void push(Node* t) {
  if (!t || !t->rev) return; //!
  swap(t->l, t->r); //!
  for (Node* c : {t->l, t->r}) if (c) c->rev ^= 1; //!
  t->rev = false; //!
}
void pull(Node* t) {
  t->size = 1 + size(t->l) + size(t->r);
  t->sum = t->val + sum(t->l) + sum(t->r); //!
}
// (first k elements, rest)
pair<Node*, Node*> split(Node* t, int k) {
  if (!t) return {};
  push(t);
  if (size(t->l) >= k) {
    auto [a, b] = split(t->l, k);
    t->l = b, pull(t);
    return {a, t};
  }
  auto [a, b] = split(t->r, k - size(t->l) - 1);
  t->r = a, pull(t);
  return {t, b};
}
Node* merge(Node* a, Node* b) {
  if (!a || !b) return a ? a : b;
  if (a->pri > b->pri) {
    push(a), a->r = merge(a->r, b), pull(a);
    return a;
  }
  push(b), b->l = merge(a, b->l), pull(b);
  return b;
}
// --- uses ---
// Each returns the new root.
Node* insert(Node* t, int pos, ll v) {
  auto [a, b] = split(t, pos);
  return merge(merge(a, new Node(v)), b);
}
Node* erase(Node* t, int pos) {
  auto [a, b] = split(t, pos);
  auto [m, c] = split(b, 1);
  delete m;
  return merge(a, c);
}
Node* reverse(Node* t, int l, int r) { // [l, r)
  auto [a, b] = split(t, l);
  auto [m, c] = split(b, r - l);
  if (m) m->rev ^= 1;
  return merge(merge(a, m), c);
}
ll rangeSum(Node*& t, int l, int r) {
  auto [a, b] = split(t, l);
  auto [m, c] = split(b, r - l);
  ll s = sum(m);
  t = merge(merge(a, m), c);
  return s;
}
