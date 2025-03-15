// https://cses.fi/problemset/result/12350190/

#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n,q; cin>>n>>q;
  int pa[n][32];
  for(int i=0;i<n;++i){
    cin>>pa[i][0];
    --pa[i][0];
  }
  for(int j=0;j<31;++j) for(int i=0;i<n;++i)
    pa[i][j+1]=pa[pa[i][j]][j];
  while(q--){
    int x,k; cin>>x>>k; --x;
    for(int i=0;i<32;++i) if(k>>i&1){
      x=pa[x][i];
    }
    cout<<x+1<<'\n';
  }
  return 0;
}


