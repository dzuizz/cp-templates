// https://cses.fi/problemset/task/1688/

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5;
const int LOG=18;
int n, q, pa[MAXN][LOG], dep[MAXN];
int lca(int a, int b) {
  if(dep[a] > dep[b])
    swap(a, b);
  for(int j=LOG-1; j>=0; --j) if(dep[pa[b][j]] >= dep[a])
    b = pa[b][j];
  if(a == b) return a;
  for(int j=LOG-1; j>=0; --j) if(pa[a][j] != pa[b][j])
    a = pa[a][j], b = pa[b][j];
  return pa[a][0];
}
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n >> q;
  for(int i=1; i<n; ++i) {
    int e; cin >> e;
    pa[i][0] = --e;
    dep[i] = dep[e] + 1;
  }

  for(int j=0; j<LOG-1; ++j) for(int i=0; i<n; ++i)
    pa[i][j+1] = pa[pa[i][j]][j];

  while(q--) {
    int a, b; cin >> a >> b;
    cout << lca(--a, --b) + 1 << '\n';
  }
  return 0;
}

