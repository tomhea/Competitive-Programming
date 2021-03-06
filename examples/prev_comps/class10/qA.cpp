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
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<pii> vii;
typedef vector<vector<ll>> graph;
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

typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
ll Kruskal(vector<iii>& edges, ll n) {
    sort(edges.begin(), edges.end());
    unionfind components(n);
    ll mst_cost = 0;
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
    ll t, n, m, l, s, i, j, x, e;
    cin >> t;
    times(t){
        vector<iii> g;
        bitset<100000> init;
        cin >> n >> m >> l >> s;
        times(s) {
            cin >> x;
            init.set(x);
        }
        times(m){
            cin >> i >> j >>e;
            g.push_back({e+l, {i,j}});
            if(init[j]){
                g.push_back({0, {0,j}});
            }
            if(init[i]){
                g.push_back({0, {i,0}});
            }
        }
        ll res = Kruskal(g, n+1);
        cout << res << endl;
    }

    return 0;
}
