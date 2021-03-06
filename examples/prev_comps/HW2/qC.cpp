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
typedef vector<vu> vvu;
typedef vector<vd> vvd;

typedef vector<vii> vvii;
typedef vector<vuu> vvuu;
typedef vector<vdd> vvdd;

struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};

#define bestWeight 1000

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int n,w;
    cin >> n;
    vi canbe(2*bestWeight+1, 0); canbe[0] = 1;
    while (n--) {
        cin >> w;
        for (int i = 2*bestWeight-w; i >=0; i--) if (canbe[i]) canbe[i+w] = 1;
    }
    for (int i = 0; i <= bestWeight; i++) {
        if (canbe[bestWeight+i]) {
            cout << bestWeight+i << endl;
            break;
        }
        if (canbe[bestWeight-i]) {
            cout << bestWeight-i << endl;
            break;
        }
    }

    return 0;
}
