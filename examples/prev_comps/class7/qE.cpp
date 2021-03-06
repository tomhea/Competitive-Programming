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


#define BIGMOD 1000000007


int main() {
    int N;
    ull n;
    string W, w;
    map<string, ull> dict;

    while (cin >> N >> W) {
        dict.clear(); while(N--) { cin >> w >> n; dict.insert({w, n}); }
        n = W.size();
        vu suffixPoss(n+1, 0); suffixPoss[n] = 1;
        for (int i = n-1; i >= 0; i--) {
            for (int len = 1; len <= n-i; len++) {
                string suf = W.substr(i, len);
                auto poss = dict.find(suf);
                if (poss != dict.end()) {
                    suffixPoss[i] = (suffixPoss[i] + (poss->second) * suffixPoss[i+len]) % BIGMOD;
                }
            }
        }
        cout << suffixPoss[0] << endl;
    }

    return 0;
}
