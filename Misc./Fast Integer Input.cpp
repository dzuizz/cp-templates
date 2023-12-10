// Super Fast Non-negative Integer Input
// to be reviewed

#include <bits/stdc++.h>
using namespace std;

inline int readInt() {
    int x = 0;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') ch = getchar_unlocked();
    while (ch >= '0' && ch <= '9'){
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar_unlocked();
    }
    return x;
}

signed main() {

}