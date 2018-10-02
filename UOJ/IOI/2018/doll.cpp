#include <bits/stdc++.h>
#include "doll.h"
using namespace std;
#define pb push_back
#define VI vector <int> 
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid (l + (r - l) / 2)

const int inf = 1e7;
int m, n, T;
vector < pair <int, int > > vec;
VI a, c, x, y, rev, pos;

inline int dfs(int l, int r, int rt) {
  if (l == r) {
    return l > T - n ? a[pos[l]] : inf;
  }
  int lc = dfs(l, mid, ls);
  int rc = dfs(mid + 1, r, rs);
  if (lc == inf && rc == inf)
    return inf;
  x.pb(lc); y.pb(rc);
  return -(int) x.size();
}

void create_circuit(int M, VI A) {
  m = M; a = A; a.pb(0); n = a.size();
  int L = -1;
  for (T = 1; T < n; T <<= 1) L ++;
  rev.resize(T); pos.resize(T + 1);
  for (int i = 0; i < T; i ++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << L);
  for (int i = T - n; i < T; i ++)
    vec.pb({rev[i], i});
  sort(vec.begin(), vec.end());
  fill(pos.begin(), pos.end(), -1);
  for (int i = 0; i < (int) vec.size(); i ++) {
    pos[vec[i].second + 1] = i;
  }
  for (int i = 1; i <= T; i ++)
    if (pos[i] == -1) pos[i] = inf;
  int rt = dfs(1, T, 1);
  c.resize(m + 1);
  for (int i = 0; i <= m; i ++)
    c[i] = rt;
  for (auto &i : x) if (i == inf) i = rt;
  for (auto &i : y) if (i == inf) i = rt;
  answer(c, x, y);
}

