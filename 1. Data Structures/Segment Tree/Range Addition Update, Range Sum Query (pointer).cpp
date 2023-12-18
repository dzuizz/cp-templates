// Range Addition Update, Range Sum Query with Lazy Propagation and Lazy Nodes (pointer)

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

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, q; cin >> n >> q;

    root = new node(1, n);

    while (q--) {
        int t; cin >> t;

        if (t == 1) {
            int l, r, k; cin >> l >> r >> k;
            root->upd(l, r, k);
        } else {
            int l, r; cin >> l >> r;
            cout << root->qry(l, r) << '\n';
        }
    }
}