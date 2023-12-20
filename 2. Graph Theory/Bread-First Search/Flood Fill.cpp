// Floodfill with Breadth First Search (BFS)
// https://cses.fi/problemset/task/1192/

#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int n, m; cin >> n >> m;

    string grid[n];
    bool vis[n][m]; memset(vis, false, sizeof(vis));
    pair<int, int> dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 0; i < n; i++) cin >> grid[i];

    int ans = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.' || vis[i][j]) continue;

            q.push({i, j});
            vis[i][j] = true;
            ans++;
            
            while (!q.empty()) {
                pair<int, int> cur = q.front();
                q.pop();
                for (auto d : dir) {
                    int x = cur.first + d.first;
                    int y = cur.second + d.second;

                    if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '.' && !vis[x][y]) {
                        q.push({x, y});
                        vis[x][y] = true;
                    }
                }
            }
        }
    }
    
    cout << ans << '\n';
}