// https://cses.fi/problemset/task/1131

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2e5+5;
vector<int> adj[MAXN];

pair<int, int> dfs(int i, int p) {
  pair<int, int> ret = {0, i};
  for (int &x: adj[i]) {
    if (x == p) continue;
    pair<int, int> tmp = dfs(x, i);
    ++tmp.first;
    ret = max(ret, tmp);
  }
  return ret;
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N;
  cin >> N;

  for (int i = 1; i < N; ++i) {
    int u, v; cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  pair<int, int> d1 = dfs(1, 0);
  pair<int, int> d2 = dfs(d1.second, 0);

  cout << d2.first << '\n';
  return 0;
}

// Time Complexity: O(N)
// Space Complexity: O(N)
// N = number of nodes
