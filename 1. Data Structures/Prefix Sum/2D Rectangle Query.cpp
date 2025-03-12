// https://cses.fi/problemset/task/1652/

#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N, Q;
  cin >> N >> Q;

  int prefSum[N+1][N+1];
  memset(prefSum, 0, sizeof prefSum);

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      char c; cin >> c;
      prefSum[i][j] = prefSum[i-1][j] + prefSum[i][j-1] + (c == '*') - prefSum[i-1][j-1];
    }
  }

  while (Q--) {
    int i1, j1, i2, j2;
    cin >> i1 >> j1 >> i2 >> j2;
    cout << prefSum[i2][j2] - prefSum[i1-1][j2] - prefSum[i2][j1-1] + prefSum[i1-1][j1-1] << '\n';
  }
  return 0;
}


