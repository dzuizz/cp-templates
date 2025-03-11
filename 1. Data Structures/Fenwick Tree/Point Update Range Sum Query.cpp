// https://cses.fi/problemset/task/1648

#include<bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 200005;
int N, Q, fw[MAXN];

void add(int idx, int v) {
  for (++idx; idx <= N; idx += idx & -idx)
    fw[idx] += v;
}
int sum(int idx) {
  int ret = 0;
  for (++idx; idx > 0; idx -= idx & -idx)
    ret += fw[idx];
  return ret;
}
int sum(int l, int r) {
  return sum(r) - sum(l - 1);
}

signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  
  cin >> N >> Q;

  int A[N];
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    add(i, A[i]);
  }

  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int k, u;
      cin >> k >> u; --k;
      add(k, u - A[k]);
      A[k] = u;
    } else if (t == 2) {
      int a, b;
      cin >> a >> b; --a, --b;
      cout << sum(a, b) << '\n';
    }
  }
  return 0;
}


