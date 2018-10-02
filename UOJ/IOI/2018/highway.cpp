#include <bits/stdc++.h>
#include "highway.h"
using namespace std;
#define VI vector <int>
#define pb push_back
const int N = 3e5 + 233;
vector < pair <int, int> > edge;
VI G[N];
int e, rx, ry, n, A, B, m, dist;
int dx[N], dy[N], bfnx[N], bfny[N];
inline int gao(int l, int r) {
  VI h(m, 0);
  for (int k = l; k <= r; k ++)
    h[k] = 1;
  return ask(h);
}

inline int find_edge(void) {
  int l = 0, r = m - 1;
  while (l < r) {
    int mid = l + (r - l) / 2;
    if (gao(0, mid) != dist) r = mid;
    else l = mid + 1;
  }
  return r; 
}

inline void bfs(int s, int *d, int *bfn) {
  for (int i = 0; i < n; i ++)
    d[i] = -1;
  queue <int> q;
  int bfs_clock = 0;
  q.push(s); d[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    bfn[u] = ++ bfs_clock;
    for (int &v : G[u]) {
      if (d[v] == -1) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
}

inline int check(int l, VI &p) {
  VI ins(n, 0);
  for (int k = l; k < (int) p.size(); k ++)
    ins[p[k]] = 1;
  VI h(m, 0);
  for (int i = 0; i < (int) edge.size(); i ++) {
    if (ins[edge[i].first] || ins[edge[i].second])
      h[i] = 1;
  }
  return ask(h);
}

inline int doit(int rt, VI p, int *bfn) {
  auto cmp = [&] (int a, int b) {
               return bfn[a] < bfn[b];
             };
  sort(p.begin(), p.end(), cmp);
  int l = 0, r = (int) p.size() - 1;
  while (l < r) {
    int mid = l + (r - l + 1) / 2;
    if (check(mid, p) != dist) l = mid;
    else r = mid - 1;
  }
  return p[r];
}

void find_pair(int N, VI U, VI V, int _A, int _B) {
  n = N; A = _A; B = _B; m = U.size();
  dist = gao(233, -233);
  for (int i = 0; i < m; i ++) {
    edge.pb({U[i], V[i]});
    G[U[i]].pb(V[i]);
    G[V[i]].pb(U[i]);
  }
  e = find_edge();
  rx = edge[e].first;
  ry = edge[e].second;
  bfs(rx, dx, bfnx);
  bfs(ry, dy, bfny);
  VI S, T;
  for (int i = 0; i < n; i ++)
    if (dx[i] < dy[i]) S.pb(i);
    else T.pb(i);
  int s = doit(rx, S, bfnx);
  int t = doit(ry, T, bfny);
  return answer(s, t);
}
