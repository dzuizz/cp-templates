// Z Algorithm for pattern matching
// https://judge.yosupo.jp/problem/zalgorithm

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> zalgorithm(string s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    z[0] = n;
    return z;
}

signed main() {
    string s; cin >> s;
    vector<int> ans = zalgorithm(s);

    for (int i = 0; i < ans.size(); i++) cout << ans[i] << ' ';
    cout << '\n';
}

// Time complexity: O(n)
// Resources:
// * https://cp-algorithms.com/string/z-function.html