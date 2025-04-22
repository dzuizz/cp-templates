// https://www.luogu.com.cn/problem/P3834
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N=200005;
inline int read(){
  #define num ch-'0'
  char ch; int res;
  while(!isdigit(ch=getchar_unlocked()));
  for(res=num;isdigit(ch=getchar_unlocked());res=(res<<3)+(res<<1)+num);
  #undef num
  return res;
}
int sum[N<<4],ls[N<<4],rs[N<<4];
int a[N],b[N],t[N];
int n,q,m,_ptr;
void upd(int&o,int pre,int l,int r,int x){
  if(!o) o=++_ptr;
  sum[o]=sum[pre]+1;
  if(l==r) return;
  int m=(l+r)>>1;
  if(x<=m) rs[o]=rs[pre],upd(ls[o],ls[pre],l,m,x);
  else ls[o]=ls[pre],upd(rs[o],rs[pre],m+1,r,x);
}
int qry(int u,int v,int l,int r,int k){
  if(l>=r) return l;
  int x=sum[ls[v]]-sum[ls[u]];
  int m=(l+r)>>1;
  if(k<=x) return qry(ls[u],ls[v],l,m,k);
  else return qry(rs[u],rs[v],m+1,r,k-x);
}
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  n=read(),q=read();
  for(int i=1;i<=n;++i) b[i]=a[i]=read();
  sort(b+1,b+n+1);
  m=unique(b+1,b+n+1)-b-1;
  for(int i=1;i<=n;++i)
    upd(t[i],t[i-1],1,m,lower_bound(b+1,b+m+1,a[i])-b);
  while(q--){
    int l=read(),r=read(),k=read();
    int i=qry(t[l-1],t[r],1,m,k);
    cout<<b[i]<<'\n';
  }
  return 0;
}

