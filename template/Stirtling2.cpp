namespace {
  const int mo = 998244353;
  inline int add(int x, int y) {
    if((x += y) >= mo) x -= mo;
    return x;
  }
  inline int sub(int x, int y) {
    if((x -= y) < 0) x += mo;
    return x;
  }
  inline int mul(int x, int y) {
    return 1LL * x * y % mo;
  }
  inline int pw(int a, int k) {
    int ans = 1;
    for (; k; k >>= 1, a = mul(a, a))
      if (k & 1) ans = mul(ans, a);
    return ans;
  }
  inline int inv(int n) {
    return pw(n, mo - 2);
  }
}

namespace binom {
  const int N = 3e5 + 233;
  int fac[N], ifac[N];
  inline void init(void) {
    int m = 3e5;
    fac[0] = 1;
    for (int i = 1; i <= m; i ++)
      fac[i] = mul(fac[i - 1], i);
    ifac[m] = inv(fac[m]);
    for (int i = m - 1; i >= 0; i --)
      ifac[i] = mul(ifac[i + 1], i + 1);
  }

  inline int C(int n, int m) {
    if (n < 0) return 0;
    else if (m == n || m == 0) return 1;
    else return mul(fac[n], mul(ifac[m], ifac[n - m]));
  }
}
using namespace binom;

namespace Poly {
  const int N = 3e5 + 233;
  const int G = 3;
  int rev[N], m, n;
  inline void init(int _n) {
    m = _n; n = 1;
    int L = -1;
    while (n < m + m)
      n <<= 1, ++ L;
    for (int i = 0; i < n; i ++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << L);
  }
  inline void FFT(int *p, int fff) {
    for(int i = 0; i < n; i ++)
      if(i < rev[i])
        swap(p[i], p[rev[i]]);
    for(int l = 2; l <= n; l <<= 1) {
      int wn = pw(G, (mo - 1) / l);
      if(fff == -1) wn = inv(wn);
      for(int *a = p, m = l >> 1; a != p + n; a += l) {
        for(int k = 0, w = 1; k < m; k ++, w = mul(w, wn)) {
          int x = a[k], y = mul(a[k + m], w);
          a[k] = add(x, y);
          a[k + m] = sub(x, y);
        }
      }
    }
    if(fff == -1) {
      int invn = inv(n);
      for(int i = 0; i < n; i ++)
        p[i] = mul(p[i], invn);
    }
  }
  inline void cov(int *a, int *b, int sz) {
    init(sz);
    FFT(a, 1); FFT(b, 1);
    for (int i = 0; i < n; i ++)
      a[i] = mul(a[i], b[i]);
    FFT(a, -1);
  }
}
int ta[N], tb[N], S[N];

inline void Stirling2(void) {
  memset(ta, 0, sizeof ta);
  memset(tb, 0, sizeof tb);
  for (int k = 0; k <= K; k ++)
    ta[k] = mul(ifac[k], pw(k, K));
  for (int k = 0; k <= K; k ++)
    tb[k] = mul(ifac[k], (k) & 1 ? mo - 1 : 1);
  Poly::cov(ta, tb, K + 1);
  for (int k = 0; k <= K; k ++)
    S[k] = ta[k];
}
