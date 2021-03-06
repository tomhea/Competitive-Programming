#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;
typedef vector<int> vi;

typedef pair<int, int> pii;
typedef pair<int, pii> iii;
typedef vector<vi> vvi;

const int INF = 1e9;


/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
                p[v] = u;
            }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

int cInt;
int assign_c2i(map<string, int>& c2i, const string& s) {
    auto r = c2i.find(s);
    if (r == c2i.end()) { c2i.insert({s,cInt}); return cInt++; }
    return r->second;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int s,r,f,t, temp,t1;
	cin >> s >> r >> f >> t;
	vector<iii> g;
	string country;
	map<string, int> c2i;
	cInt = 2;
    for (int i = 0; i < r; i++) {
        cin >> country;
        assign_c2i(c2i, country);
        g.push_back({1,{0,cInt-1}});
    }
    for (int i = 0; i < f; i++) {
        cin >> country;
        assign_c2i(c2i, country);
        g.push_back({1,{cInt-1, 1}});
    }
    for (int i = 0; i < t; i++) {
        int bt = cInt; cInt += 2;
        g.push_back({1,{bt,bt+1}});
        cin >> temp; for (int j = 0; j < temp; j++) {
            cin >> country;
            t1 = assign_c2i(c2i, country);
            g.push_back({1,{t1,bt}});
            g.push_back({1,{bt+1,t1}});
        }
    }

    cout << EdmondsKarp (cInt, g, 0, 1) << endl;
    return 0;
}
