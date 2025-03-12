// https://codebreaker.xyz/problem/exponentiate

#include <bits/stdc++.h>
using namespace std;
#define int long long

int binpow(int a, int b, int m) {
  int res = 1;
  while (b) {
    if (b & 1) res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int t; cin >> t;
  while (t--) {
    int a, b, m; cin >> a >> b >> m;
    cout << binpow(a%m, b, m) << '\n';
  }
}

