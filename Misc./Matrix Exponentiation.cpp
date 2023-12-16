// Matrix Exponentiation
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1170

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, b;

int mod(int a, int b) {
    return a & ((1 << b) - 1);
}

struct Matrix {
    int m[2][2];
    
    Matrix() {
        memset(m, 0, sizeof(m));
    }
    
    void create() {
        m[0][0] = 0;
        m[0][1] = 1;
        m[1][0] = 1;
        m[1][1] = 1;
    }
    
    void print() {
        for (int i : {0, 1}) {
            for (int j : {0, 1}) {
                cout << m[i][j] << " ";
            }
            cout << '\n';
        }
    }
    
    Matrix operator * (Matrix &oth) {
        Matrix res;
        for(int i : {0, 1}) {
            for(int j : {0, 1}) {
                for(int k : {0, 1}) {
                    res.m[i][j] = mod(mod(mod(res.m[i][j], b) + mod(m[i][k], b) * mod(oth.m[k][j], b), b), b);
                }
            }
        }
        return res;
    }
    
    void operator *= (Matrix &oth) {
        *this = *this * oth;
    }
};

Matrix t;

Matrix expo(int p) {
    if (p == 1) return t;
    Matrix tmp = expo(p/2);
    tmp *= tmp;
    
    if (p&1) return tmp * t;
    else return tmp;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    t.create();
    while (cin >> n >> b) {
        if (n == 0) {
            cout << "0\n";
            continue;
        }

        Matrix res = expo(n);
        cout << mod(res.m[1][0], b) << '\n';
    }
}
