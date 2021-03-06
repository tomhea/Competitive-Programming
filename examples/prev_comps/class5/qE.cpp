#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <unordered_map>
#define times(x) int _##x = x; while(_##x--)
#define loop(x,n) int x=0; for(; x < n; ++x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef vector<vector<pii>> vvii;

const int INF = 1e9;
bool BellmanFord(const vvii& g, int s, vi& d);
int main() {
    int w, h, g, e, gx, gy, x1, y1, x2, y2, t;
    while (cin >> w >> h && (w != 0 || h != 0)) {
        cin >> g;
        set<int> graves;
        graves.empty();
        times(g){
            cin >> gx >> gy;
//            gx--;
//            gy--;
            graves.insert(gx+gy*w);
        }

        cin >> e;
        unordered_map<int, pii> holes;
        times(e){
            cin >> x1 >> y1 >> x2 >> y2 >> t;
//            x1--; x2--; y1--; y2--;
            holes[x1 + y1*w] = make_pair(x2+w*y2, t);
        }

        vvii g(w*h);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) if (y!=h-1 || x != w-1){
                if (holes.find(x + y*w) != holes.end()){
                    g[y*w+x].push_back(holes.find(x + y*w)->second);
                } else{
                    if (x - 1 >= 0 && graves.find(y * w + x - 1) == graves.end()) g[y * w + x].push_back(make_pair(y * w + x - 1, 1));
                    if (x + 1 < w && graves.find(y * w + x + 1) == graves.end()) g[y * w + x].push_back(make_pair(y * w + x + 1, 1));
                    if (y - 1 >= 0 && graves.find(y * w + x - 1*w) == graves.end()) g[y * w + x].push_back(make_pair(y * w + x - 1*w, 1));
                    if (y + 1 < h && graves.find(y * w + x + 1*w) == graves.end()) g[y * w + x].push_back(make_pair(y * w + x + 1*w, 1));
                }

            }
        }
        vi dist(w*h);
        bool res = BellmanFord(g, 0, dist);
        if (res){
            cout <<"Never" << endl;
        } else if (dist[w*h-1] == INF){
            cout << "Impossible" << endl;
        } else{
            cout << dist[w*h-1] << endl;
        }
    }
    return 0;
}

bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (int u = 0; u < g.size(); ++u) for (pii e : g[u]) {
                int v = e.first;
                int w = e.second;
                // relax the edge
                if (d[u] < INF && d[u]+w < d[v]) {
                    d[v] = d[u]+w;
                    changed = true;
                }
            }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}