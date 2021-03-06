#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1e9;


// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
void Dijkstra(const vvii& g, int s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < dist[v]) {
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
}


int main() {
    int n, k;
    while (cin >> n >> k) {
        vi T(n);
        for (int i = 0; i < n; i++) cin >> T[i];
        int s = 100*n, e = s+1;
        vvii g(s+2);
        vvi switches(100);
        string line;
        getline(cin, line);
        for (int i = 0; i < n; i++) {
            getline(cin, line);
            istringstream iss(line);
            int temp, last;
            iss >> last;
            switches[last].push_back(i);
            while (iss >> temp) {
                switches[temp].push_back(i);
                int cost = T[i] * (temp - last);
                g[100 * i + temp].push_back({100 * i + last, cost});
                g[100 * i + last].push_back({100 * i + temp, cost});
                last = temp;
            }
        }
        for (int f = 0; f < 100; f++) {
            for (int i1 : switches[f]) {
                for (int i2 : switches[f]) {
                    if (i1 == i2) continue;
                    g[i1*100+f].push_back({i2*100+f, 60});
                    g[i2*100+f].push_back({i1*100+f, 60});
                }
            }
        }
        for (int i = 0; i < n; i++) {
            g[s].push_back({i*100, 0});
            g[i*100+k].push_back({e, 0});
        }
        vi dist(s+2);
        Dijkstra(g, s, dist);
        if (dist[e] == INF) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << dist[e] << endl;
        }
    }

    return 0;
}
