#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<vii> vvii;

#define INF 1000000

int DijkstraUpdateLassSafe(const vvii& g, int s, vi &d, vi &safe, int K) {
    int lessSafe = 0;
    d[s] = 0;
    priority_queue<pii, vii, greater<pii>> q;
    q.push({0, s});
    if (safe[s]) {
        lessSafe++;
        safe[s] = 0;
    }
    while (!q.empty()) {
        pii front = q.top(); q.pop();
        int dist = front.first, u = front.second;
        if (dist > d[u]) continue;
        for (pii next : g[u]) {
            int v = next.first, w = next.second;
            if (d[u]+w < d[v]) {
                d[v] = d[u]+w;
                q.push({d[v], v});
                if (d[v] < K && safe[v]) {
                    lessSafe++;
                    safe[v] = 0;
                }
            }
        }
    }
    return lessSafe;
}

int main() {
    int N,M,A,K, t1,t2,d, B;
    while (cin >> N >> M >> A >> K) {
        if (N == 0) break;
        vi farFromBase(N,INF);
        vvii g(N); for (int i = 0; i < N; i++) g[i] = vii();
        for (int i = 0; i < M; i++) {
            cin >> t1 >> t2 >> d; t1--; t2--;
            g[t1].push_back({t2,d});
            g[t2].push_back({t1,d});
        }
        vi safe (N, 1);
        int numSafe = N;
        for (int i = 0; i < A; i++) {
            cin >> B; B--;
            numSafe -= DijkstraUpdateLassSafe(g, B, farFromBase, safe, K);
            cout << numSafe << endl;
        }
        cout << endl;
    }
    return 0;
}
