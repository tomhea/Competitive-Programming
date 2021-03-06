#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

#define EPS 1e-9
void pointInPoly(vii poly, int x, int y) {
    bool below;
    bool touch = false;
    bool on = false;
    int count = 0;
    int added = 0;
    int n = poly.size();

    int x1,y1, x2,y2;
    for (int i = 0; i < n+added; i++) {
        x1 = poly[i%n    ].first; y1 = poly[i%n    ].second;
        x2 = poly[(i+1)%n].first; y2 = poly[(i+1)%n].second;

        if ((y1 > y) && (y2 > y)) { below = false; touch = true; continue; }
        if ((y1 < y) && (y2 < y)) { below = true ; touch = true; continue; }

        if (y1 == y2) {
            if (y != y1) continue;
            if (((x1 <= x) && (x <= x2)) || ((x2 <= x) && (x <= x1))) {on = true; break;}
            continue;
        }
        double x_int;
        if (x2 == x1) x_int = x1;
        else {
            double a = double(y2 - y1) / double(x2 - x1);
            double b = y1 - a * x1;
            x_int = (y - b) / a;
        }

        if (abs(x_int - x) < EPS) {on = true; break;}

        if (x_int < x) { below = y1 < y; touch = true; continue; }

        if (y == y2) {
            below = y1 < y;
            touch = true;
            continue;
        }

        if (y == y1) {
            if (!touch) {
                added++;
                continue;
            }
            if (below != (y2 < y)) count++;
            continue;
        }

        if ((y1 <= y) && (y <= y2)) {
            count++;
            below = true;
            touch = true;
            continue;
        }

        if ((y2 <= y) && (y <= y1)) {
            count++;
            below = false;
            touch = true;
            continue;
        }

        below = y1 < y;
        touch = true;
    }
    if (on) cout << "on" << endl;
    else {
        if (count % 2 == 0) cout << "out" << endl;
        else cout << "in" << endl;
    }
}


int main() {
    int n,m, x,y;
    while (cin >> n) {
        if (n == 0) return 0;
        vii poly;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            poly.push_back({x,y});
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            pointInPoly(poly, x, y);
        }
    }
}
