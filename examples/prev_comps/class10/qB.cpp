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
struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
int Kruskal(vector<iii>& edges, int n) {
    sort(edges.begin(), edges.end());
    unionfind components(n);
    int mst_cost = 0;
    for (iii e : edges) {
        if (components.find(e.second.first)
            != components.find(e.second.second)) {
            components.Union(e.second.first, e.second.second);
            mst_cost += e.first; }}
    return mst_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t, m, c, d, i, j;
    cin >> t;
    times(t){
        vector<iii> g;
        cin >> m >> c;
        for (int k = 0; k < (c*(c-1))/2; ++k) {
            cin >> i >> j >>d;
            g.push_back({d, {i,j}});
        }
        int res = Kruskal(g, c);
        if (res + c <= m){
            cout<< "yes" << endl;
        } else {
            cout<< "no" << endl;
        }
    }

    return 0;
}
