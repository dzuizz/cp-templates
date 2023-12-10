// Matrix Exponentiation
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2481

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 1e9 + 7;
vector<int> masks;
int pos[128];
string s;
int t, n;

int add(int a, int b) {
    return (a % M + b % M) % M;
}

int mul(int a, int b) {
    return (a % M * b % M) % M;
}

bool valid(int mask) {
    return __builtin_popcount(mask) == 4;
}

bool inRange(int x) {
    return 0 <= x && x < 7;
}

struct Matrix {
    int m[35][35];

    Matrix() {
        memset(m, 0, sizeof(m));
    }

    void create() {
        for (int mask : masks) {
            int ind = 0, pos2[4];

            for (int i=0; i<7; i++)
                if ((mask >> i) & 1)
                    pos2[ind++] = i;

            for (int i : {-1, 1}) {
                int pt1 = pos2[0] + i;
                if (!inRange(pt1)) continue;

                for (int l : {-1, 1}) {
                    int pt2 = pos2[1] + l;
                    if (!inRange(pt2) || pt2 == pt1) continue;

                    for (int j : {-1, 1}) {
                        int pt3 = pos2[2] + j;
                        if (!inRange(pt3) || pt3 == pt2 || pt3 == pt1) continue;

                        for (int k : {-1, 1}) {
                            int pt4 = pos2[3] + k;
                            if (!inRange(pt4) || pt4 == pt3 || pt4 == pt2 || pt4 == pt1) continue;

                            int newMask = 0;

                            newMask |= (1 << pt1);
                            newMask |= (1 << pt2);
                            newMask |= (1 << pt3);
                            newMask |= (1 << pt4);

                            m[pos[newMask]][pos[mask]]++;
                        }
                    }
                }
            }
        }
    }

    Matrix operator*(Matrix oth) {
        Matrix res;

        for (int i = 0; i < 35; i++)
            for (int l = 0; l < 35; l++)
                for (int j = 0; j < 35; j++)
                    res.m[i][l] = add(res.m[i][l], mul(m[i][j], oth.m[j][l]));

        return res;
    }

    void operator*=(Matrix oth) {
        *this = *this * oth;
    }
};

Matrix trans;

Matrix expo(int p) {
    if (p == 1) return trans;
    Matrix temp = expo(p / 2);
    temp *= temp;

    if (p & 1) return temp * trans;
    return temp;
}

int dp(int row, int mask) {
    if (row == n) return 1;

    int ind = 0, pos[4];
    for (int i=0; i<7; i++)
        if ((mask >> i) & 1)
            pos[ind++] = i;

    int res = 0;
    for (int i : {-1, 1}) {
        int pt1 = pos[0] + i;
        if (!inRange(pt1)) continue;

        for (int l : {-1, 1}) {
            int pt2 = pos[1] + l;
            if (!inRange(pt2) || pt2 == pt1) continue;

            for (int j : {-1, 1}) {
                int pt3 = pos[2] + j;
                if (!inRange(pt3) || pt3 == pt2 || pt3 == pt1) continue;

                for (int k : {-1, 1}) {
                    int pt4 = pos[3] + k;
                    if (!inRange(pt4) || pt4 == pt3 || pt4 == pt2 || pt4 == pt1) continue;
                    int newMask = 0;

                    newMask |= (1 << pt1);
                    newMask |= (1 << pt2);
                    newMask |= (1 << pt3);
                    newMask |= (1 << pt4);

                    res += dp(row + 1, newMask) % M;
                    res %= M;
                }
            }
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int ind = 0;
    for (int i=0; i<(1<<7); i++) {
        if (valid(i)) {
            masks.push_back(i);
            pos[i] = ind++;
        }
    }

    cin >> t;
    while (t--) {
        cin >> n;
        int mask = 0;
        for (int i=0; i<7; i++) {
            int x; cin >> x;
            if (x > 0) mask |= (1 << i);
        }

        if (n == 1) {
            cout << "1\n";
            continue;
        }

        trans = Matrix();
        trans.create();
        Matrix res = expo(n - 1);
        int ans = 0;

        for (int i=0; i<35; i++) {
            ans += res.m[i][pos[mask]];
            ans %= M;
        }

        cout << ans << '\n';
    }
}