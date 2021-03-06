// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <bitset>
#include <iomanip>

using namespace std;

typedef pair<double, double> dd;
typedef pair<double, int> di;
typedef pair<int, double> id;
typedef pair<dd, double> ddd;
typedef vector<double> vd;
typedef vector<id> vid;
typedef vector<di> vdi;
typedef vector<vid> vvid;
typedef vector<ddd> vddd;

const int INF = 1e9;


/********** Shortest Paths **********/

// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist), were distance is the maximal weight on the route.
// time: O(ElogV).
void DijkstraMaxDouble(const vvid& g, int s, vd& dist) {
    dist = vd(g.size(), INF);
    dist[s] = 0.0;
    priority_queue<di, vdi, greater<di>> q;
    q.push({0.0, s});
    while (!q.empty()) {
        di front = q.top(); q.pop();
        double d = front.first; int u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (id next : g[u]) {
            int v = next.first; double w = next.second;
            if (max(dist[u],w) < dist[v]) {
                dist[v] = max(dist[u],w);
                q.push({dist[v], v});
            }
        }
    }
}



int main() {
    int T, n;
    double w, x,y,r;
    cin >> T;
    while (T--) {
        cin >> w >> n;
        vddd circles(n);
        for (int i = 0; i < n; i++) { cin >> x >> y >> r; circles[i] = {{x,y}, r}; }

        int L = n, R = n+1;
        vvid g(n+2);
        g[L].push_back({R, w});
        g[R].push_back({L, w});
        for (int i1 = 0; i1 < n; i1++) {
            for (int i2 = i1+1; i2 < n; i2++) {
                ddd c1 = circles[i1], c2 = circles[i2];
                double x1 = c1.first.first, y1 = c1.first.second, r1 = c1.second;
                double x2 = c2.first.first, y2 = c2.first.second, r2 = c2.second;
                double dist = max(0.0, sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) - (r1+r2));
                g[i1].push_back({i2, dist});
                g[i2].push_back({i1, dist});
            }
        }
        for (int i = 0; i < n; i++) {
            double x = circles[i].first.first, r = circles[i].second;
            double distL = max(0.0, x-r), distR = w - min(w, x+r);
            g[L].push_back({i, distL});
            g[i].push_back({L, distL});
            g[i].push_back({R, distR});
            g[R].push_back({i, distR});
        }
        vd dist(n+2);
        DijkstraMaxDouble(g, L, dist);
        cout << setprecision(10) << fixed << dist[R]/2.0 << endl;
    }

    return 0;
}
