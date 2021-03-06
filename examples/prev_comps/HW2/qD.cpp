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

int greedy(int amount, vi& coins, vi& res){
    uint bigger = coins.size()-1;
    while (amount - coins[bigger] < 0){
        bigger--;
    }
    return res[amount] = res[amount - coins[bigger]] +1;
}

int dp(int amount, vi& coins, vi& res){
    int _min = INF;
    for (int c : coins) {
        _min = amount - c >= 0 ? min(_min, res[amount - c] + 1) : _min;
    }
    return res[amount] = _min;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, c, s;
    vi coins;
    cin >> n;
    times(n){
        cin >> c;
        coins.push_back(c);
    }
    s = coins[n-1] + coins[n-2];
    vi res_dp(s, 0);
    vi res_greedy(s, 0);
    for (int i = 1; i < s; ++i) {
        if(dp(i, coins, res_dp) != greedy(i, coins, res_greedy)){
            cout << "non-canonical" << endl;
            return 0;
        }
    }
    cout << "canonical" << endl;
    return 0;
}
