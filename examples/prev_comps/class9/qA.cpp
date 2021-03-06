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
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
typedef vector<piii> viii;

viii plats;
int h[10000] = {0};
struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,y,x1,x2, tot=0;
    cin >> n;
    times(n){
        cin >> y >>x1 >> x2;
        plats.push_back({y,{x1,x2}});
    }
    sort(plats.begin(), plats.end());
    for(piii p : plats){
        y =p.first; x1 = p.second.first; x2=p.second.second;
        tot += y - h[x1];
        tot += y - h[x2-1];
        for(int x = p.second.first; x < p.second.second; x++){
            h[x] = max(h[x], y);
        }
    }
    cout << tot << endl;

    return 0;
}
