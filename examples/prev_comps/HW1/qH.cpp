#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;


bool bfs(const vvi& g, int s, int t) {
    if (s == t) return true;
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u])
            if (!visible[v]) {
                if (v == t) return true;
                visible[v] = true;
                q.push(v);
            }
    }
    return false;
}

int main() {
    int m,n, N=26;
    char t1,t2;
    cin >> m >> n;
    string s1,s2;
    vvi g(N); for (int i = 0; i < N; i++) g[i] = vi();
    for (int i = 0; i < m; i++) {       // create graph
        cin >> t1 >> t2;
        g[t1-'a'].push_back(t2-'a');
    }

    for (int i = 0; i < n; i++) {   // for every word translation
        cin >> s1 >> s2;
        int len = s1.size();
        if (len != s2.size()) { cout << "no" << endl; continue; }
        bool bad = false;
        for (int j = 0; j < len; j++) if (!bfs(g, s1[j]-'a', s2[j]-'a')) { bad = true; break; } // for every letter translation
        cout << (bad ? "no" : "yes") << endl;
    }

    return 0;
}
