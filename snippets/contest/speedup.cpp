/**
 * Name: Speedups
 * Description: Pragmas go above all includes. Drop `avx2` if the
 *   judge rejects it. `readInt` is several times faster than `cin`.
 */
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

int gc() {
  static char buf[1 << 16];
  static size_t len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, sizeof buf, stdin);
  return pos < len ? buf[pos++] : -1;
}
ll readInt() {
  int c = gc();
  while (c != '-' && (c < '0' || c > '9')) c = gc();
  bool neg = c == '-';
  if (neg) c = gc();
  ll x = 0;
  for (; '0' <= c && c <= '9'; c = gc())
    x = 10 * x + c - '0';
  return neg ? -x : x;
}
