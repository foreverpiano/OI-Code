namespace {
  const int mo = 1e9 + 7;
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

}

