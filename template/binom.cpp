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
