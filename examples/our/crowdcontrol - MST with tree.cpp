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
#include <unordered_map>
#include <numeric>
#include <iomanip>
#define loop(x,n) for(int x=0; x < n; ++x)
#define times(x) loop(__##x,x)
#define EPS 1e-9
#define INF 1e9
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
typedef vector<iii> edges_v;

struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};

struct unionfind {
    vector<int> rank;
    vector<int> parent;
    explicit unionfind (int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++) parent[i]=i;
    }

    int find(int x) {
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if(q==p) return;
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};
int Kruskal(vector<iii>& edges, int n, graph& mst) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst[e.second.first].push_back(e.second.second);
            mst[e.second.second].push_back(e.second.first);
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}
void bfs(const graph & g, int s, vector<int>& d, vector<int>& parent) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    d.assign(g.size(),INF); d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u]+1;
                parent[v] = u;
                q.push(v);
            }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b, c;
    cin >> n >> m;
    edges_v edges;
    graph mst(n);
    graph g(n);
    unordered_map<ii, int, hash_pair> index;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        g[a].push_back(b);
        g[b].push_back(a);
        edges.push_back({-c, {a, b}});
        index[{a,b}] = i;
        index[{b,a}] = i;
    }
    Kruskal(edges,n, mst);
    vi distn*(n);
    vi par(n, -1);
    bfs(mst, 0, dist, par);

    vi block;
    int cur = n-1;
    int prev = -1;
    while (cur != -1){
        for(int u : g[cur]){
            if(u != par[cur] && u != prev){
                block.push_back(index[{cur, u}]);
            }
        }
        prev = cur;
        cur = par[cur];
    }
    if(block.empty()){
        cout << "none" << endl;
    } else{
        sort(block.begin(), block.end());
        block.erase(unique(block.begin(), block.end()), block.end());
        for (int i = 0; i < block.size(); ++i) {
            if (i) cout << " ";
            cout << block[i] << " ";
        }
    }
    return 0;
}
