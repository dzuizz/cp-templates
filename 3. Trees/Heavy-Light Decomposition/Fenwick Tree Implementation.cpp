// https://codebreaker.xyz/problem/grassplant

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e5+5;
int n,m,_ptr;
namespace fw{  // 1-indexed
  int fw1[MAXN],fw2[MAXN];
  void add(int fw[],int idx,int d){
    for(; idx<=n; idx+=idx&-idx)
      fw[idx]+=d;
  }
  void add(int l,int r,int d){
    add(fw1,l,d), add(fw1,r+1,-d);
    add(fw2,l,d*(l-1)), add(fw2,r+1,-d*r);
  }
  int sum(int fw[],int idx){
    int ret=0;
    for(; idx>0; idx-=idx&-idx)
      ret+=fw[idx];
    return ret;
  }
  int sum(int idx){
    return sum(fw1,idx)*idx - sum(fw2,idx);
  }
  int sum(int l,int r){  // [l, r]
    return sum(r)-sum(l-1);
  }
}
vector<int> adj[MAXN];
int pre[MAXN],pos[MAXN],hp[MAXN],pa[MAXN],dep[MAXN],ss[MAXN];
void dfs_ss(int i,int p){
  ss[i]=1;
  if(adj[i][0]==p && adj[i].size()>1)  // Ensure parent is last
    swap(adj[i][0], adj[i][1]);
  for(auto&x:adj[i]){
    if(x==p) continue;
    dfs_ss(x,i);
    ss[i]+=ss[x];
    if(ss[x]>ss[adj[i][0]])  // Found heavier child
      swap(x, adj[i][0]);
  }
}
void dfs_hld(int i,int p){
  pre[i]=++_ptr;  // 1-based
  for(auto&x:adj[i]){
    if(x==p) continue;
    pa[x]=i;
    dep[x]=dep[i]+1;
    hp[x]=(x==adj[i][0]?hp[i]:x);
    dfs_hld(x,i);
  }
  pos[i]=_ptr;
}
signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin>>n>>m;

  for(int i=0;i<n-1;++i){
    int u,v; cin>>u>>v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  dfs_ss(1, 0);
  hp[1]=1;
  dfs_hld(1, 0);

  while(m--){
    char c; cin>>c;
    int x,y; cin>>x>>y;
    if(c=='P'){  // Update
      while(hp[x]!=hp[y]){
        if(dep[hp[x]]<dep[hp[y]]) swap(x,y);
        fw::add(pre[hp[x]],pre[x],1);
        x=pa[hp[x]];
      }
      if(pre[x]>pre[y]) swap(x,y);
      if(x!=y) fw::add(pre[x]+1,pre[y],1);
    }else{  // Query
      int ans=0;
      while(hp[x]!=hp[y]){
        if(dep[hp[x]]<dep[hp[y]]) swap(x,y);
        ans+=fw::sum(pre[hp[x]],pre[x]);
        x=pa[hp[x]];
      }
      if(pre[x]>pre[y]) swap(x,y);
      if(x!=y) ans+=fw::sum(pre[x]+1,pre[y]);
      cout<<ans<<'\n';
    }
  }
  return 0;
}


