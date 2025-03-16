// https://open.kattis.com/problems/coveredwalkway

#include<bits/stdc++.h>
using namespace std;
#define int long long
struct Line{
  mutable int k,m,p;
  bool operator<(const Line&o) const { return k<o.k; }
  bool operator<(int x) const { return p<x; }
};
struct ConvexHull : multiset<Line, less<>> {
  static const int inf = INT64_MAX;
  int div(int a,int b){ return a/b - ((a^b)<0&&a%b); }
  bool isect(iterator x,iterator y){
    if(y==end()) return x->p=inf, 0;
    if(x->k==y->k) x->p=x->m>y->m?inf:-inf;
    else x->p=div(y->m-x->m,x->k-y->k);
    return x->p>=y->p;
  }
  void add(int k,int m){
    auto z=insert({k,m,0}), y=z++, x=y;
    while(isect(y,z)) z=erase(z);
    if(x!=begin()&&isect(--x,y)) isect(x,y=erase(y));
    while((y=x)!=begin()&&(--x)->p>=y->p) isect(x,erase(y));
  }
  int qry(int x){
    assert(!empty());
    auto l=*lower_bound(x);
    return l.k*x+l.m;
  }
};
signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n,c; cin>>n>>c;
  ConvexHull hull;
  int run=0;
  for(int i=0;i<n;++i){
    int k; cin>>k;
    hull.add(2*k,-run-k*k);
    run=-hull.qry(k)+k*k+c;
  }
  cout<<run<<'\n';
  return 0;
}

