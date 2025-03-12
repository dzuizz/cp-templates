// https://cses.fi/problemset/task/1095/

#include<bits/stdc++.h>
using namespace std;
#define int long long
int binpow(int a, int b, int m){
  if(b==0) return 1;
  if(b==1) return a;
  int tmp=binpow(a, b>>1, m);
  tmp = tmp * tmp % m;
  if(b&1) tmp = tmp * a % m;
  return tmp;
}
signed main() {
  int n; cin>>n;
  for(int i=0;i<n;++i){
    int a,b; cin>>a>>b;
    cout<<binpow(a,b,1e9+7)<<'\n';
  }
}


