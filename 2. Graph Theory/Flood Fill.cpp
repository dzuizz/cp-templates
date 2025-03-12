// https://cses.fi/problemset/task/1192/

#include<bits/stdc++.h>
using namespace std;
#define int long long
pair<int, int> dir[]={
  {0, 1},
  {1, 0},
  {0, -1},
  {-1, 0}
};
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N,M; cin>>N>>M;

  bool vis[N][M]; memset(vis, 0, sizeof(vis));
  for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) {
    char c; cin>>c;
    vis[i][j]=c=='#';
  }

  int ans = 0;  // # of c.c
  queue<pair<int,int>> q;
  for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) {
    if(vis[i][j]) continue;
    vis[i][j] = 1;
    ++ans;
    q.emplace(i, j);
    while(q.size()){
      pair<int, int> cur = q.front(); q.pop();
      for(auto &p:dir){
        int nxi = cur.first + p.first;
        int nxj = cur.second + p.second;
        if (0 <= nxi && nxi < N && 0 <= nxj && nxj < M && !vis[nxi][nxj]){
          q.emplace(nxi,nxj);
          vis[nxi][nxj] = 1;
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

