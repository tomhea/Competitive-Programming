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
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<double> vd;

typedef pair<int, int> pii;
typedef pair<ull, ull> puu;
typedef pair<double, double> pdd;

typedef vector<pii> vii;
typedef vector<puu> vuu;
typedef vector<pdd> vdd;

typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vu> vvu;
typedef vector<vd> vvd;

typedef vector<vii> vvii;
typedef vector<vuu> vvuu;
typedef vector<vdd> vvdd;

#define INF 1e18

vvvi memo;
ull f(ull k, ull s, ull m) {
    if (memo[k][s][m] != -1) return memo[k][s][m];
    if (s == m) return memo[k][s][m] = 0;
    if (k == 1) return memo[1][s][m] = m*(m+1)/2 - s*(s+1)/2;
    ull best = INF;
    for (ull i = s+1; i <= m; i++) {
        best = min(best, i+max(f(k-1, s, i-1), f(k, i, m)));
    }
    return memo[k][s][m] = best;
}


int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    ull N, k,m;
    cin >> N;
    while (N--) {
        cin >> k >> m;
        memo = vvvi(k+1, vvi(m+1, vi(m+1, -1)));
        cout << f(k, 0, m) << endl;
    }

    return 0;
}


