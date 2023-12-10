// Binary Exponentiation
// https://codebreaker.xyz/problem/exponentiate

#include <bits/stdc++.h>
using namespace std;

#define int long long

int binpow(int a, int b, int m) {
    if (b == 0) return 1;
    if (b == 1) return a;
    int res = binpow(a, b/2, m);
    res = (res*res)%m;
    if (b%2) res = (res*a)%m;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int a, b, m; cin >> a >> b >> m;
        cout << binpow(a%m, b, m) << '\n';
    }
}