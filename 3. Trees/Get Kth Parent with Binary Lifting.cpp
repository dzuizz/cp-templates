// https://cses.fi/problemset/task/1687/

#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n,q; cin>>n>>q;
  int pa[n+1][18]; pa[0][0] = pa[1][0] = 0;
  for(int i=2; i<=n; ++i) {
    cin>>pa[i][0];
  }
  for(int j=0; j<17; ++j) for(int i=0; i<=n; ++i)
    pa[i][j+1] = pa[pa[i][j]][j];

  while(q--) {
    int x,k; cin>>x>>k;
    int ans=x;
    for(int j=0; j<18; ++j) if(k>>j&1)
      ans=pa[ans][j];
    cout<<(ans?ans:-1)<<'\n';
  }
  return 0;
}

