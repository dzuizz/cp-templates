// All-in-one struct implementation of a Tree data structure

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 500005;
const int LOG = 20;

struct Tree { // 0-based index
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> pa;
    vector<int> sz, dep, dist, pre, post; // sz = subtree size, dep = depth of node, dist = distance from root, pre = preorder, post = postorder
    int n, _TIME;

    Tree(int _n, vector<vector<pair<int, int>>> &_adj): n(_n), adj(_adj) {
        pa.assign(n, vector<int>(LOG)); // Parent array
        dist.assign(n, 0);
        post.assign(n, 0);
        pre.assign(n, 0);
        dep.assign(n, 0);
        sz.assign(n, 1);

        pa[0][0] = -1;
        _TIME = -1;

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
        pre[cur] = ++_TIME;
        for (auto &p : adj[cur]) {
            if (p.first == pa[cur][0]) continue;
            dep[p.first] = dep[cur] + 1;
            dist[p.first] = dist[cur] + p.second; // Change to weight[cur][p.first] for weighted tree
            pa[p.first][0] = cur;

            init(p.first);
            sz[cur] += sz[p.first];
        }
        post[cur] = _TIME;
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

    pair<int, int> dfs(int cur, int prev) { // (dist, node)
        pair<int, int> ret = {0, cur};
        for (auto &p : adj[cur]) {
            if (p.first == prev) continue;
            pair<int, int> tmp = dfs(p.first, cur);
            tmp.first += p.second;
            ret = max(ret, tmp);
        }
        return ret;
    }

    pair<int, pair<int, int>> diameter() {
        pair<int, int> d1 = dfs(0, -1);
        pair<int, int> d2 = dfs(d1.second, -1);
        return make_pair(d2.first, make_pair(d1.second, d2.second));
    }

    int dist(int u, int v) {
        return dist[u] + dist[v] - 2*dist[lca(u, v)];
    }

    bool isAncestor(int u, int v) {
        return pre[u] <= pre[v] && post[v] <= post[u];
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
// init(): O(N log N)
// lca(): O(log N)
// dfs(): O(N)
// diameter(): O(N)
// dist(): O(log N)
// isAncestor(): O(1)
// Space Complexity: O(N log N)