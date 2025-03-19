// https://codebreaker.xyz/problem/grassplant

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct node {
    node *lf, *rg;
    int l, r, mid, val, lazy;

    node (int _l, int _r): l(_l), r(_r) {
        mid = (l+r)/2;
        lf = nullptr;
        rg = nullptr;
        val = 0;
        lazy = 0;
    }

    void prop() {
        if (l == r) return;
        if (lazy != 0) {
            lf->val += lazy * (mid-l+1);
            lf->lazy += lazy;
            rg->val += lazy * (r-mid);
            rg->lazy += lazy;

            lazy = 0;
        }
    }

    int qry(int x, int y) {
        if (r < x || l > y) return 0;
        if (x <= l && r <= y) return val;
        if (lf == nullptr) create();
        prop();
        return lf->qry(x, y) + rg->qry(x, y);
    }

    void upd(int x, int y, int v) {
        if (r < x || l > y) return;
        if (x <= l && r <= y) {
            val += v * (r-l+1);
            lazy += v;
            return;
        }
        if (lf == nullptr) create();
        prop();
        lf->upd(x, y, v);
        rg->upd(x, y, v);
        val = lf->val+rg->val;
    }

    void create() {
        if (l != r) {
            lf = new node(l, mid);
            rg = new node(mid+1, r);
        }
    }
} *root;

const int MAXN = 1e5+5;

vector<int> adj[MAXN];
int pre[MAXN], post[MAXN], hp[MAXN], pa[MAXN], dep[MAXN], sz[MAXN];
int n, m, _TIME;

void dfs_ss(int i, int p) {
    sz[i] = 1;

    if (adj[i][0] == p && adj[i].size() > 1)
        swap(adj[i][0], adj[i][1]);

    for (auto &x : adj[i]) {
        if (x == p) continue;
        dfs_ss(x, i);
        sz[i] += sz[x];

        if (sz[x] > sz[adj[i][0]])
            swap(x, adj[i][0]);
    }
}

void dfs_hld(int i, int p) {
    pre[i] = ++_TIME;

    for (auto &x : adj[i]) {
        if (x == p) continue;

        pa[x] = i;
        dep[x] = dep[i] + 1;
        hp[x] = (x == adj[i][0] ? hp[i] : x);
        dfs_hld(x, i);
    }

    post[i] = _TIME;
}

signed main() {
    cin >> n >> m;

    for (int i=0; i<n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    root = new node(1, n);

    dfs_ss(1, 0);
    hp[1] = 1;
    dfs_hld(1, 0);

    while (m--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        
        if (c == 'P') {
            while (hp[x] != hp[y]) {
                if (dep[hp[x]] < dep[hp[y]]) swap(x, y);

                root->upd(pre[hp[x]], pre[x], 1);
                x = pa[hp[x]];
            }

            if (pre[x] > pre[y]) swap(x, y);
            if (x != y) root->upd(pre[x]+1, pre[y], 1);
        } else if (c == 'Q') {
            int ans = 0;

            while (hp[x] != hp[y]) {
                if (dep[hp[x]] < dep[hp[y]]) swap(x, y);

                ans += root->qry(pre[hp[x]], pre[x]);
                x = pa[hp[x]];
            }

            if (pre[x] > pre[y]) swap(x, y);
            if (x != y) ans += root->qry(pre[x]+1, pre[y]);

            cout << ans << '\n';
        }
    }
}

