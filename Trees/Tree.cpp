// https://cses.fi/problemset/task/1674

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 5e5+5;
vector<int> children[MAXN];
int pa[MAXN], sz[MAXN], n, a, b;

void dfs(int cur) {
    for (auto &nx : children[cur]) {
        dfs(nx);
        sz[cur] += sz[nx] + 1;
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;

    pa[1] = 0;
    for (int i=2; i<=n; i++) {
        int x; cin >> x;
        pa[i] = x;
        children[x].push_back(i);
    }

    dfs(1);

    for (int i=1; i<=n; i++) {
        cout << sz[i] << " ";
    }
    cout << '\n';
}