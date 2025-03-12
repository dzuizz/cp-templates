// https://cses.fi/problemset/task/2064/

#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int m=1e9+7;
int binpow(int a,int b){
  int ret=1;
  while(b){
    if(b&1) ret=ret*a%m;
    a=a*a%m,b>>=1;
  }
  return ret;
}
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n; cin>>n;
  if(n&1){  // n is odd <=> no valid bracket sequences
    cout<<"0\n";
    return 0;
  }
  int ans=1;
  for(int i=2; i<=(n>>1); ++i){
    ans = ans * (4*i-2) % m;
    ans = ans * binpow(i+1,m-2) % m;
  }
  cout << ans << '\n';
  return 0;
}


