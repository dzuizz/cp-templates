// All-in-one implementation of a Tree data structure in a struct
// https://cses.fi/problemset/task/1674

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 500005;
const int LOG = 20;

struct Tree { // 0-based index
    vector<vector<pair<int, int>>> adjlist;
    vector<vector<int>> pa;
    vector<int> sz, dep, dist; // sz = subtree size, dep = depth of node, dist = distance from root
    vector<pair<int, int>> range;
    int n, ptr;

    Tree(int _n, vector<vector<pair<int, int>>> &_adj): n(_n), adjlist(_adj) {
        pa.assign(n, vector<int>(LOG)); // Parent array
        range.assign(n, {0, 0});
        dist.assign(n, 0);
        dep.assign(n, 0);
        sz.assign(n, 1);

        pa[0][0] = -1;
        ptr = -1;

        init();
    }

    void init() {
        init(0);

        for (int j=1; j<LOG; j++) {
            for (int i=0; i<n; i++) {
                pa[i][j] = pa[pa[i][j-1]][j-1];
            }
        }
    }

    void init(int cur) {
        range[cur].first = ++ptr;
        for (auto &p : adjlist[cur]) {
            if (p.first == pa[cur][0]) continue;
            dep[p.first] = dep[cur] + 1;
            dist[p.first] = dist[cur] + p.second; // Change to weight[cur][p.first] for weighted tree
            pa[p.first][0] = cur;

            init(p.first);
            sz[cur] += sz[p.first];
        }
        range[cur].second = ptr;
    }

    int lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);

        for (int i=LOG-1; i>=0; i--) {
            if (pa[a][i] != -1 && dep[pa[a][i]] >= dep[b]) {
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

    int dist(int u, int v) {
        return dist[u] + dist[v] - 2*dist[lca(u, v)];
    }

    bool isAncestor(int u, int v) {
        return range[u].first <= range[v].first && range[v].second <= range[u].second;
    }
} *tree;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;

    vector<vector<pair<int, int>>> graph(n);

    for (int i=1; i<n; i++) {
        int x; cin >> x; x--;
        graph[x].push_back({i, 0});
    }

    tree = new Tree(n, graph);

    
}

// Time Complexity:
//      init(): O(NlogN)
//      lca(): O(logN)
//      dist(): O(logN)
//      isAncestor(): O(1)
//      Total: O(NlogN)