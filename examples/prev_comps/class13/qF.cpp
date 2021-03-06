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
typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int w, n;
    cin >> n;
    graph mst(n);
    edges_v edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> w;
            if(j >= i+1){
                edges.push_back({w,{i,j}});
            }
        }
    }
    Kruskal(edges,n, mst);
    set<ii> e;
    for (int k = 0; k < mst.size(); ++k) {
        for (int i = 0; i < mst[k].size(); ++i) {
            e.insert({min(mst[k][i], k), max(mst[k][i], k)});
        }
    }

    for (auto p : e ){
        cout << p.first +1 << " " << p.second +1 << endl;
    }
    return 0;
}
