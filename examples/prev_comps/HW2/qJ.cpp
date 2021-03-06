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

int can[33];
int memo[33][641][641];
int n;

int func(int i, int l2m, int m2h){
    if(memo[i][l2m][m2h] != -1) return memo[i][l2m][m2h];
    if (i == n){
        return memo[i][l2m][m2h] = l2m + m2h;
    }
    //h
    int res = func(i+1, l2m, m2h + can[i]);
    //m
    res = min(res, func(i+1, l2m + min(can[i], m2h), abs(m2h - can[i])));
    //l
    if(can[i] < l2m){
        res = min(res, func(i+1, l2m - can[i], m2h));
    } else if(can[i] < l2m + m2h){
        res = min(res, func(i+1, can[i] - l2m, l2m + m2h - can[i]));
    } else{
        res = min(res, func(i+1, m2h, can[i] - l2m - m2h));
    }
    return memo[i][l2m][m2h] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int j = 0; j < t; ++j) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> can[i];
        }
        memset(memo, -1, sizeof(int)*33*641*641);
        cout << "Case " << j+1 << ": " << func(0,0,0) << endl;

    }
    return 0;
}
