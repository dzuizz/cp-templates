// Lowest Common Ancestor (LCA) with Binary Lifting
// https://cses.fi/problemset/task/1688/

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2e5+5;
const int LOG = 18;

vector<int> adj[MAXN];
int pa[MAXN][LOG], dep[MAXN];

void dfs(int cur) {
    for (auto &nx : adj[cur]) {
        dep[nx] = dep[cur] + 1;
        dfs(nx);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i=LOG-1; i>=0; i--) {
        if (dep[pa[a][i]] >= dep[b]) {
            a = pa[a][i];
        }
    }

    if (a == b) return a;

    for (int i=LOG-1; i>=0; i--) {
        if (pa[a][i] != pa[b][i]) {
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    return pa[a][0];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;

    dep[1] = 0, pa[1][0] = 1;
    for (int i=2; i<=n; i++) {
        cin >> pa[i][0];
        adj[pa[i][0]].push_back(i);
    }

    dfs(1);

    for (int i=1; i<=n; i++) {
        for (int j=1; j<LOG; j++) {
            pa[i][j] = pa[pa[i][j-1]][j-1];
        }
    }
    
    while (q--) {
        int a, b; cin >> a >> b;

        cout << lca(a, b) << '\n';
    }
}

// Time complexity: O(nlogn + qlogn)
// n = number of nodes
// q = number of queries