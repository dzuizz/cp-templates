// https://cses.fi/problemset/task/1192

#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n,m; cin>>n>>m;
  vector<pair<int,int>> adj[n];
  for(int i=0; i<m; ++i){
    int a,b,c; cin>>a>>b>>c;
    adj[--a].emplace_back(c,--b);
  }
  for(int i=0; i<n; ++i)
    sort(adj[i].begin(),adj[i].end());
  int dis[n]; memset(dis,0x3f,sizeof dis);
  dis[0] = 0;
  priority_queue<pair<int,int>>pq;
  pq.emplace(0,0);
  while(pq.size()){
    pair<int,int> cur=pq.top(); pq.pop();
    if(-cur.first>dis[cur.second]) continue;
    for(auto&p:adj[cur.second]){
      if(-cur.first+p.first>=dis[p.second]) continue;
      dis[p.second]=p.first-cur.first;
      pq.emplace(-dis[p.second],p.second);
    }
  }
  for(int i=0; i<n; ++i)
    cout<<dis[i]<<" ";
  cout<<'\n';
  return 0;
}


