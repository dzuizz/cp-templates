// Super Fast Integer Input
// to be reviewed

#include <bits/stdc++.h>
using namespace std;

#define int long long

inline int readInt() {
    int x = 0;
    bool neg = false;
    register char c = getchar_unlocked();
    while (c < '0' || c > '9') {
        if (c == '-') neg = true;
        c = getchar_unlocked();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar_unlocked();
    }
    return neg ? -x : x;
}
