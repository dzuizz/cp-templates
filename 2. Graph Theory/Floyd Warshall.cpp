// https://www.spoj.com/problems/SOCIALNE/

#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;

    while (t--) {
        string s; cin >> s;
        int n = s.size();
        
        int adj[n][n]; adj[0][0] = 0;
        
        for (int j=1; j<n; j++) adj[0][j] = (s[j]=='Y'?1:1e9);
        for (int i=1; i<n; i++) {
            cin >> s;
            for (int j=0; j<n; j++) {
                if (i == j) adj[i][j] = 0;
                else adj[i][j] = (s[j]=='Y'?1:1e9);
            }
        }

        for (int k=0; k<n; k++) {
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
                }
            }
        }

        int mxVal = 0, mxInd = 0;
        for (int i=0; i<n; i++) {
            int ans = 0;
            for (int j=0; j<n; j++) {
                if (adj[i][j] == 2) ans++;
            }
            
            if (ans > mxVal) {
                mxVal = ans;
                mxInd = i;
            }
        }

        cout << mxInd << ' ' << mxVal << '\n';
    }
}