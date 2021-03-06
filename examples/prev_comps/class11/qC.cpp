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

int sum;
int dp[151][101][51];
//     c    n5   n10


int func(int left, int n5, int n10){
    if(left == 0) return 0;
    if(dp[left][n5][n10] != -1) return dp[left][n5][n10];
    int n1 = sum - 5*n5 -10*n10;
    int res = INF;
    if(n10 > 0) res = min(res, 1 + func(left-1, n5, n10-1));    //10
    if(n5 > 1) res = min(res, 2 + func(left-1, n5-2, n10));    //5+5
    if(n1 > 7) res = min(res, 8 + func(left-1, n5, n10));    //1+1+1+1+1+1
    if(n5 > 0 && n1 >2) res = min(res, 4 + func(left-1, n5-1, n10));    //5+1+1+1
    if(n10 > 0 && n1 >2) res = min(res, 4 + func(left-1, n5+1, n10-1));    //10+1+1+1

    return dp[left][n5][n10] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t, c, n1, n5, n10;
    cin >>t;
    times(t){
        memset(dp, -1, sizeof(int) * 151*101*51);
        cin >> c >> n1 >> n5 >> n10;
        sum = n1 + 5*n5 + 10*n10;
        cout << func(c, n5, n10) << endl;
    }
    return 0;
}
