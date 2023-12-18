// Range Addition Update, Range Sum Query (2 BITs approach)

#include <bits/stdc++.h>
using namespace std;

#define int long long

int ft1[100005], ft2[100005];
int n;

void add(int ft[], int idx, int val) {
    while (idx <= n) {
        ft[idx] += val;
        idx += idx & -idx;
    }
}

void range_add(int l, int r, int x) {
    add(ft1, l, x);
    add(ft1, r+1, -x);
    add(ft2, l, x*(l-1));
    add(ft2, r+1, -x*r);
}

int sum(int ft[], int idx) {
    int res = 0;
    while (idx) {
        res += ft[idx];
        idx -= idx & -idx;
    }
    return res;
}

int pref_sum(int idx) {
    return sum(ft1, idx)*idx - sum(ft2, idx);
}

int range_sum(int l, int r) {
    return pref_sum(r) - pref_sum(l-1);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    
    for (int i=1; i<=n; i++) {
        int x; cin >> x;
        range_add(i, i, x);
    }

    int q; cin >> q;
    while (q--) {
        int t; cin >> t;

        if (t) {
            int a, b, c; cin >> a >> b >> c; a++, b++;
            range_add(a, b, c);
        } else {
            int x, y; cin >> x >> y; x++, y++;
            cout << range_sum(x, y) << '\n';
        }
    }
}