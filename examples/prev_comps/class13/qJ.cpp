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

const int N = 2e6+1; // limit for array size
int n; // array size
int t[2 * N] = {0};
void build() { // build the tree
for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}
void modify(int p, int value) { // set value at position p
for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}
int query(int l, int r) { // sum on interval [l, r)
int res = 0;
for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
if (l&1) res += t[l++];
if (r&1) res += t[--r];
}
return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k, l, r, b;
    char cmd;
    cin >> n  >> k;
    build();
    for (int i = 0; i < k; ++i) {
        cin >> cmd;
        if(cmd == 'F'){
            cin >> b;
            b--;
            modify(b, !query(b,b+1));
        }else{
            cin >> l >> r;
            cout << query(l-1,r) << endl;
        }
    }




    return 0;
}
