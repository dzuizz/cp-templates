// https://cses.fi/problemset/task/1647/

#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n,q; cin>>n>>q;
  int st[n][__lg(n)+1];
  for(int i=0;i<n;++i) cin>>st[i][0];
  for(int j=1;(1<<j)<=n;++j) for(int i=0;i+(1<<j)<=n;++i)
    st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
  while(q--){
    int a,b; cin>>a>>b; --a,--b;
    int k=__lg(b-a+1);
    cout<<min(st[a][k],st[b-(1<<k)+1][k])<<'\n';
  }
  return 0;
}


