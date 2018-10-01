namespace mf {
  static const int N = 2333;
  static const int M = 2e6 + 233;
  static const int inf = 1e16;
  struct E {
    int nxt, to, fl;
  }e[M << 1];
  int d[N], head[N], cur[N], e_cnt = 1;
  int n, s, t;
  inline void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    fill(head, head + n + 1, 0);
    e_cnt = 1;
  }
  inline void add(int u, int v, int fl) {
    e[++ e_cnt] = (E) {head[u], v, fl}; head[u] = e_cnt;
  }
  inline void link(int u, int v, int fl) {
    add(u, v, fl); add(v, u, 0);
  }
  inline bool bfs(void) {
    queue<int> q;
    fill(d, d + n + 1, -1);
    d[s] = 0; q.push(s);
    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(int i = head[u]; i; i = e[i].nxt) if(e[i].fl) {
          int v = e[i].to;
          if(!~ d[v]) d[v] = d[u] + 1, q.push(v);
        }
    }
    return d[t] != -1;
  }
  inline int dfs(int u, int f) {
    if(u == t || !f) return f;
    int used = 0, t;
    for(int i = head[u]; i; i = e[i].nxt) if(e[i].fl) {
        int v = e[i].to;
        if(d[v] != d[u] + 1) continue;
        t = dfs(v, min(f - used, e[i].fl));
        used += t; e[i].fl -= t; e[i ^ 1].fl += t;
        if(used == f) break;
      }
    if(!used) d[u] = -1;
    return used;
  }
  inline int doit(void) {
    int fl = 0;
    while(bfs()) {
      memcpy(cur, head, sizeof (int) * (n + 2));
      fl += dfs(s, inf);
    }
    return fl;
  }
}
