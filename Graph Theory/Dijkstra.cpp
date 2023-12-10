// Dijkstra's Algorithm to find shortest path from Node 1 to Node N
// https://codebreaker.xyz/problem/dijkstra

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second

typedef pair<int, int> ii;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int v, e; cin >> v >> e;

    vector<ii> adj[v];
    int dist[v];

    for (int i = 0; i < v; i++) dist[i] = INT64_MAX;
    for (int i = 0; i < e; i++) {
        int u, v, wi; cin >> u >> v >> wi; u--, v--;
        adj[u].push_back(ii(v, wi));
        adj[v].push_back(ii(u, wi));
    }

    priority_queue<ii> q; // (dist, node)
    q.push(ii(-0, 0));
    while(!q.empty()) {
        ii cur = q.top(); q.pop();
        int curDist = -cur.fi, curNode = cur.se;

        if (curDist > dist[curNode]) continue;

        for (int i = 0; i < adj[curNode].size(); i++) {
            ii nx = adj[curNode][i];
            int nxDist = curDist + nx.se;
            if (nxDist < dist[nx.fi]) {
                dist[nx.fi] = nxDist;
                q.push(ii(-nxDist, nx.fi));
            }
        }   
    }
    cout << dist[v-1] << '\n';
}
