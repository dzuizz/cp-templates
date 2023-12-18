// APSP (All Pairs Shortest Path) with Binary Lifting
// https://cses.fi/problemset/task/1135/

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> adjlist[(int)2e5+5];
int pa[(int)2e5+5][20], dep[(int)2e5+5];

void dfs(int cur) {
    for (auto &nx : adjlist[cur]) {
        if (nx == pa[cur][0]) continue;

        pa[nx][0] = cur;
        dep[nx] = dep[cur] + 1;
        dfs(nx);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    
    for (int i=19; i>=0; i--) {
        if (dep[pa[a][i]] >= dep[b]) {
            a = pa[a][i];
        }
    }

    if (a == b) return a;

    for (int i=19; i>=0; i--) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i];
            b = pa[b][i];
        }
    }

    return pa[a][0];
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    
    for (int i=1; i<n; i++) {
        int u, v; cin >> u >> v;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    pa[1][0] = 1;
    dfs(1);

    for (int j=1; j<20; j++) {
        for (int i=1; i<=n; i++) {
            pa[i][j] = pa[pa[i][j-1]][j-1];
        }
    }

    while (q--) {
        int u, v; cin >> u >> v;

        int w = lca(u, v);

        cout << dep[u] + dep[v] - 2*dep[w] << '\n';
    }
}

// Time Complexity: O(nlogn + qlogn)
// n = number of nodes
// q = number of queries