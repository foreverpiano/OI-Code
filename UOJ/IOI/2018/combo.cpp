#include <bits/stdc++.h>
#include "combo.h"
using namespace std;

string str[6], st;
vector <string> v;
int n, pos;

string doit(void) {
  string ans = st;
  for (int k = 2; k < n; k ++) {
    string query = "";
    query += ans + v[0] + v[0];
    query += ans + v[0] + v[1];
    query += ans + v[0] + v[2];
    query += ans + v[1];
    int p = press(query);
    if (p == k + 1)
      ans += v[0];
    else if (p == k)
      ans += v[1];
    else
      ans += v[2];
  }
  if (press(ans + v[0]) == n)
    ans += v[0];
  else if (press(ans + v[1]) == n)
    ans += v[1];
  else
    ans += v[2];
  return ans;
}

string guess_sequence(int N) {
  n = N;
  str[1] = "A"; str[2] = "B"; str[3] = "X"; str[4] = "Y";
  if (press(str[1] + str[2])) {
    if (press(str[1]))
      st = str[1], pos = 1;
    else
      st = str[2], pos = 2;
  } else {
    if (press(str[3]))
      st = str[3], pos = 3;
    else
      st = str[4], pos = 4;
  }
  for (int k = 1; k <= 4; k ++)
    if (k != pos)
      v.push_back(str[k]);
  if (n == 1)
    return st;
  else
    return doit();
}
