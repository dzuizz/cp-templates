// Union Find Disjoint Set (UFDS)
// https://tlx.toki.id/problems/sg-noi-2014/B/

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int parent, size = 1;
    vector<int> v;
};

vector<pair<int, pair<int, int>>> edges;
int n, e, q, cur;

Node dsu[(int) 5e5+5];
int ans[(int) 5e5+5];

int find(int n) {
    if (n == dsu[n].parent) return n;
    return dsu[n].parent = find(dsu[n].parent);
}

void merge(int a, int x) {
    a = find(a); int b = find(x);
    if (a == b) return;

    if (dsu[a].size < dsu[b].size) swap(a, b);
    
    if (find(b) == find(1))
        for (auto &x : dsu[a].v)
            ans[x] = cur;

    if (find(a) == find(1))
        for (auto &x : dsu[b].v)
            ans[x] = cur;
    
    dsu[b].parent = a;
    dsu[a].size += dsu[b].size;
    
    for (auto &x : dsu[b].v) dsu[a].v.push_back(x);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> e >> q;
    
    for(int i=1; i<=n; i++) {
        dsu[i].parent = i;
        dsu[i].v.push_back(i);
    }
    
    for (int i=1; i<=e; i++) {
        int u, v, w; cin >> u >> v >> w;
        
        edges.push_back({w, {u, v}});
    }
    sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());

    for (auto edge : edges) {
        int weight = edge.first;
        int a = edge.second.first;
        int b = edge.second.second;
        
        cur = weight;
        merge(a, b);
    }
    
    while (q--) {
        int x; cin >> x;
        cout << ans[x] << '\n';
    }
}