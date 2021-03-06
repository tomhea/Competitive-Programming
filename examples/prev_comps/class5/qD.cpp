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
#define times(x) int __##x = x; while(__##x--)
#define loop(x,n) int x=0; for(; x < n; ++x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<vi> vvi;
const int INF = 1e9;
void bfs(const vvi& g, int s, vector<int>& d );

int main() {
    int m, n;
    string s;
    while (cin >> n) {
        cin >> m;
        vvi mat(n);
        for (int i = 0; i < n; ++i) {
            cin >> s;
            for (char c : s) {
                mat[i].push_back(c - '0');
            }
        }
        vvi g(n*m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int d = mat[i][j];
                if (j - d >= 0) g[i*m + j].push_back(i*m + j - d);
                if (j + d < m) g[i*m + j].push_back(i*m + j + d);
                if (i - d >= 0) g[i*m + j].push_back(i*m + j - d*m);
                if (i + d < n) g[i*m + j].push_back(i*m + j + d*m);
            }
        }
        vi dist(n*m);
        bfs(g, 0, dist);
        if (dist[n*m-1] == INF){
            cout << "-1" << endl;
        } else{
            cout << dist[n*m-1] << endl;
        }
    }
    return 0;
}

void bfs(const vvi& g, int s, vector<int>& d ) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    d.assign(g.size(),INF); d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u]+1;
                q.push(v);
            }}}