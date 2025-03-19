// https://codebreaker.xyz/problem/fitnesscorner

#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=1e5+5;
vector<int> adj[MAXN];
int n,ss[MAXN],dif[MAXN];
void dfs_ss(int i,int p){
  ss[i]=1;
  for(auto&x:adj[i]){
    if(x==p) continue;
    if(dif[x]>0) continue;
    dfs_ss(x,i);
    ss[i]+=ss[x];
  }
}
int get_centroid(int i,int p,int sz){
  for(auto&x:adj[i]){
    if(x==p) continue;
    if(dif[x]>0) continue;
    if(ss[x]*2>sz)
      return get_centroid(x,i,sz);
  }
  return i;
}
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin>>n;

  for(int i=1;i<n;++i){
    int u,v; cin>>u>>v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  dfs_ss(1,0);

  queue<pair<int,int>> q;
  q.emplace(get_centroid(1,0,n),1);

  while(q.size()){
    auto [i,v]=q.front(); q.pop();
    dif[i]=v;
    for(auto&x:adj[i]){
      if(dif[x]>0) continue;
      int sz=ss[x];
      dfs_ss(x,0);
      q.emplace(get_centroid(x,0,sz),v+1);
    }
  }

  for(int i=1;i<=n;++i)
    cout<<(char)('A'+dif[i]-1)<<" ";
  cout<<'\n';
  return 0;
}


