// Dynamic Convex Hull Trick for DP optimization

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(int x) const { return p < x; }
};
struct DynamicLineContainer : multiset<Line, less<>> {
    // for doubles, use inf = 1/.0, div(a,b) = a / b
    static const int inf = INT64_MAX; // change accordingly
    int div(int a, int b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(int k, int m) { // insert y = kx + m
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    int query(int x) { // max query
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
// to use:
// DynamicLineContainer hull;
// hull.add(m, c);
// hull.query(x);
// to convert min queries to max queries:
// hull.add(-m, -c);
// -hull.query(x);


// Example: https://codebreaker.xyz/problem/cht
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n], b[n];

    DynamicLineContainer hull;

    for (int i=0; i<n; i++) cin >> a[i];
    for (int i=0; i<n; i++) cin >> b[i];

    int dp[n]; dp[0] = 0;
    hull.add(a[0], 0);

    for (int i=1; i<n; i++) {
        dp[i] = hull.query(b[i]);
        hull.add(a[i], dp[i]);
    }

    cout << dp[n-1] << '\n';
}