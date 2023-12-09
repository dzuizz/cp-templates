// Array Implementation of Segment Tree with Lazy Propagation (Range Update, Range Sum Query)
// https://codebreaker.xyz/problem/segmenttree2

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int val, lazy, l, r, lf, rg;
    Node(): val(0), lazy(0), lf(-1), rg(-1) {}
};

const int INF = 1e9;
const int M = 1e9 + 7;
Node segTree[(int) 2e7];
int cnt = 2;

void propagate(int idx) {
    if (segTree[idx].lazy) {
        segTree[idx].val += (segTree[idx].r - segTree[idx].l + 1) * segTree[idx].lazy;
        int mid = (segTree[idx].l + segTree[idx].r) / 2;
        
        if (segTree[idx].lf == -1) {
            segTree[idx].lf = cnt++;
            
            segTree[segTree[idx].lf].l = segTree[idx].l;
            segTree[segTree[idx].lf].r = mid;
        }
        
        if (segTree[idx].rg == -1) {
            segTree[idx].rg = cnt++;

            segTree[segTree[idx].rg].l = mid + 1;
            segTree[segTree[idx].rg].r = segTree[idx].r;
        }

        segTree[segTree[idx].lf].lazy += segTree[idx].lazy;
        segTree[segTree[idx].rg].lazy += segTree[idx].lazy;
        segTree[idx].lazy = 0;
    }
}

void update(int idx, int x, int y, int v) {
    if (segTree[idx].l == x && segTree[idx].r == y) {
        segTree[idx].lazy += v;
        propagate(idx);
        return;
    }

    int mid = (segTree[idx].l + segTree[idx].r) / 2;

    if (segTree[idx].lf == -1) {
        segTree[idx].lf = cnt++;

        segTree[segTree[idx].lf].l = segTree[idx].l;
        segTree[segTree[idx].lf].r = mid;
    }

    if (segTree[idx].rg == -1) {
        segTree[idx].rg = cnt++;

        segTree[segTree[idx].rg].l = mid + 1;
        segTree[segTree[idx].rg].r = segTree[idx].r;
    }

    if (x > mid) update(segTree[idx].rg, x, y, v);
    else if (y <= mid) update(segTree[idx].lf, x, y, v);
    else {
        update(segTree[idx].lf, x, mid, v);
        update(segTree[idx].rg, mid + 1, y, v);
    }

    propagate(segTree[idx].lf);
    propagate(segTree[idx].rg);
    segTree[idx].val = segTree[segTree[idx].lf].val + segTree[segTree[idx].rg].val;
}

int query(int idx, int x, int y) {
    propagate(idx);

    if (segTree[idx].l == x && segTree[idx].r == y) return segTree[idx].val;
    
    int mid = (segTree[idx].l + segTree[idx].r) / 2;
    if (segTree[idx].lf == -1) {
        segTree[idx].lf = cnt++;

        segTree[segTree[idx].lf].l = segTree[idx].l;
        segTree[segTree[idx].lf].r = mid;
    }

    if (segTree[idx].rg == -1) {
        segTree[idx].rg = cnt++;

        segTree[segTree[idx].rg].l = mid + 1;
        segTree[segTree[idx].rg].r = segTree[idx].r;
    }

    propagate(segTree[idx].lf);
    propagate(segTree[idx].rg);

    if (x > mid) return query(segTree[idx].rg, x, y);
    else if (y <= mid) return query(segTree[idx].lf, x, y);
    else return query(segTree[idx].lf, x, mid) + query(segTree[idx].rg, mid + 1, y);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, q; cin >> n >> q;

    segTree[1].l = 1; segTree[1].r = n;

    while (q--) {
        int t; cin >> t;
        
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            update(1, l, r, x);
        } else {
            int l, r; cin >> l >> r;
            cout << query(1, l, r) << '\n';
        }
    }
}
