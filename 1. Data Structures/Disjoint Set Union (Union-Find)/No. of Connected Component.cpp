// Count no. of conneted components in a graph using DSU (Disjoint Set Union)
// Problem link: https://cses.fi/problemset/task/1666/

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct DSU {
    vector<int> parent, size;
    int components;

    DSU(int n) {
        parent = vector<int>(n, -1);
        size = vector<int>(n, 1);
        components = n;
    }

    int find(int x) { return parent[x]==-1 ? x : parent[x] = find(parent[x]); }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return 0;
        if (size[x] < size[y]) swap(x, y);

        parent[y] = x;
        size[x] += size[y];
        components--;

        return 1;
    }
};

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    DSU dsu(n);

    while (m--) {
        int a, b; cin >> a >> b; a--, b--;
        dsu.unite(a, b);
    }

    cout << dsu.components - 1 << '\n';
    for (int i=1; i<n; i++) {
        if (dsu.find(i) != dsu.find(0)) {
            dsu.unite(i, 0);
            cout << i+1 << ' ' << 1 << '\n';
        }
    }
}