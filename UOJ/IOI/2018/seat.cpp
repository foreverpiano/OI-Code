#include <bits/stdc++.h>
#include "seats.h"
using namespace std;
#define VI vector <int>
// yx
// xx
const int N = 1e6 + 233;
int x[N], y[N], one[N], tri[N];
int n, m, sz;
vector < vector <int> > a;
namespace bit {
#define mid (l + (r - l) / 2)
#define ls (rt << 1)
#define rs (rt << 1 | 1)
  const int SZ = 4 * N;
  pair <int, int> node[SZ], tag[SZ];
  int cnt[SZ];
  inline void ps(int rt) {
    node[rt] = min(node[ls], node[rs]);
    cnt[rt] = 0;
    if (node[rt] == node[ls])
      cnt[rt] += cnt[ls];
    if (node[rt] == node[rs])
      cnt[rt] += cnt[rs];                                       
  }
  inline void up(pair <int, int> &a, pair <int, int> b) {
    a.first += b.first;
    a.second += b.second;
  }
  inline void PushTag(int rt, pair <int, int> t) {
    up(tag[rt], t);
    up(node[rt], t);
  }
  inline void pd(int rt) {
    if (tag[rt].first == 0 && tag[rt].second == 0)
      return ;
    PushTag(ls, tag[rt]);
    PushTag(rs, tag[rt]);
    tag[rt] = {0, 0};
  }
  inline void build(int l, int r, int rt) {
    if (l == r) {
      node[rt] = {one[l], tri[l]};
      cnt[rt] = 1;
      return ;
    }
    build(l, mid, ls);
    build(mid + 1, r, rs);
    ps(rt);
  }
  inline void add(int ql, int qr, pair <int, int> v,
                  int l, int r, int rt) {
    if (ql > qr) return ;
    if (ql == l && qr == r) {
      PushTag(rt, v);
      return ;
    }
    pd(rt);
    if (qr <= mid)
      add(ql, qr, v, l, mid, ls);
    else if (ql > mid)
      add(ql, qr, v, mid + 1, r, rs);
    else {
      add(ql, mid, v, l, mid, ls);
      add(mid + 1, qr, v, mid + 1, r, rs);
    }
    ps(rt);
  }
  inline bool isok(pair <int, int> a) {
    return a.first == 4 && a.second == 0;
  }
  inline int gao(void) {
    return isok(node[1]) * cnt[1];
  }
}

inline void yo(int i, int j, int f) {
  int tmp[] = {a[i][j], a[i + 1][j], a[i][j + 1], a[i + 1][j + 1]};
  sort(tmp, tmp + 4);
  bit::add(tmp[0], tmp[1] - 1, {f, 0}, 1, sz, 1);
  bit::add(tmp[2], tmp[3] - 1, {0, f}, 1, sz, 1);
}

void give_initial_chart(int H, int W, VI R, VI C) {
  n = H; m = W;
  a.resize(n + 2);
  for (int i = 0; i <= n + 1; i ++)
    a[i].resize(m + 2);
  for (int i = 0; i <= n + 1; i ++)
    for (int j = 0; j <= m + 1; j ++)
      a[i][j] = n * m + 1;
  for (int i = 0; i < n * m; i ++) {
    a[R[i] + 1][C[i] + 1] = i + 1;
    x[i + 1] = R[i] + 1;
    y[i + 1] = C[i] + 1;
  }
  sz = n * m;
  bit::build(1, sz, 1);
  for (int i = 0; i <= n; i ++)
    for (int j = 0; j <= m; j ++) {
      int tmp[] = {a[i][j], a[i + 1][j], a[i][j + 1], a[i + 1][j + 1]};
      sort(tmp, tmp + 4);
      one[tmp[1]] --; one[tmp[0]] ++;
      tri[tmp[3]] --; tri[tmp[2]] ++;
    }
  for (int i = 1; i <= sz; i ++)
    one[i] += one[i - 1], tri[i] += tri[i - 1];
  bit::build(1, sz, 1);
}

inline void gao(int x, int y, int f) {
  yo(x, y, f);
  yo(x - 1, y, f);
  yo(x, y - 1, f);
  yo(x - 1, y - 1, f);
}

int swap_seats(int u, int v) {
  ++ u; ++ v;
  int &s = a[x[u]][y[u]];
  int &t = a[x[v]][y[v]];
  gao(x[u], y[u], -1);
  gao(x[v], y[v], -1);
  swap(s, t);
  swap(x[u], x[v]);
  swap(y[u], y[v]);
  gao(x[u], y[u], 1);
  gao(x[v], y[v], 1);
  return bit::gao();
}
