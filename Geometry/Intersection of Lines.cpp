// Count no. of Intersection of Lines
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1843

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x first
#define y second

typedef pair<int, int> Point;

Point pt = Point(1e8, 1e8);
int n;

struct Line {
    Point p, q;
    
    Line(int a = 0, int b = 0, int c = 0, int d = 0) {
        p = Point(a, b);
        q = Point(c, d);
    }
};

int cross(Point A, Point B, Point C) { // -1 +1 0
    int xAB = B.x - A.x, yAB = B.y-A.y;
    int xAC = C.x - A.x, yAC = C.y-A.y;
    int ret = xAB*yAC - xAC*yAB;
    if (ret < 0) return -1;
    if (ret == 0) return 0;
    return 1;
}

bool isColinear(Line a, Line b) {
    return cross(a.p, a.q, b.p) == 0 && cross(a.p, a.q, b.q) == 0; 
}

bool isIntersect(Line a, Line b) {
    if (isColinear(a, b)) {
        return (cross(a.p, pt, b.p) != cross(a.p, pt, b.q) || cross(a.q, pt, b.p) != cross(a.q, pt, b.q)) && 
            (cross(b.p, pt, a.p) != cross(b.p, pt, a.q) || cross(b.q, pt, a.p) != cross(b.q, pt, a.q));
    }
    return cross(a.p, a.q, b.p) != cross(a.p, a.q, b.q) && cross(b.p, b.q, a.p) != cross(b.p, b.q, a.q);
}

signed main() {
    while (cin >> n, n) {
        vector<Line> v(n);
        vector<int> ans;
        
        for (int i = 0; i < n; i++) {
            double a, b, c, d; cin >> a >> b >> c >> d;
            v[i].p.x = a;
            v[i].p.y = b;
            v[i].q.x = c;
            v[i].q.y = d;
        }
        
        for (int i = 0; i < n; i++) {
            bool flag = false;
            for (int j = i + 1; j < n; j++) {
                if (isIntersect(v[i], v[j])) {
                    flag = true;
                    break;
                }
            }
            if (flag) continue;
            ans.push_back(i + 1);
        }
        cout << "Top sticks: " << ans[0];
        for(int i = 1; i < ans.size(); i++) cout << ", " << ans[i];
        cout << ".\n";
    }
}
