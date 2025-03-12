// https://codebreaker.xyz/problem/dquery

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int BLOCK_SIZE=500;
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n; cin>>n;
  int a[n]; for(auto&e:a) cin>>e;
  int q; cin>>q;
  pair<pair<int,int>,int> qry[q];
  for(int i=0;i<q;++i){
    cin>>qry[i].first.first>>qry[i].first.second;
    --qry[i].first.first, --qry[i].first.second;
    qry[i].second = i;
  }
  sort(qry,qry+q,[&](const pair<pair<int,int>,int>&a,const pair<pair<int,int>,int>&b){
    return a.first.first/BLOCK_SIZE == b.first.first/BLOCK_SIZE
    ? (a.first.first/BLOCK_SIZE)&1 ? a.first.second<b.first.second : a.first.second>b.first.second
    : a.first.first < b.first.first;
  });
  int l=0,r=-1,c[1000001],cur=0;
  memset(c,0,sizeof c);
  int ans[q];
  for(auto&p:qry){
    while(l>p.first.first)  // --l
      cur+=(c[a[--l]]++?0:1);
    while(r<p.first.second)  // ++r
      cur+=(c[a[++r]]++?0:1);
    while(l<p.first.first)  // l++
      cur-=(--c[a[l++]]?0:1);
    while(r>p.first.second)  // r--
      cur-=(--c[a[r--]]?0:1);
    ans[p.second]=cur;
  }
  for(auto&e:ans)
    cout<<e<<'\n';
  return 0;
}

