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
typedef pair<int, int> pii;

#define BIGG 1001*1001

int main() {
    vi costs;
    int N, cost;
    costs.push_back(BIGG);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> cost;
        costs.push_back(cost);
    }

    vector<vi> CellJmp(1001);
    for (auto & cells : CellJmp) cells = vi(1001, BIGG);
    CellJmp[1][0] = 0;
    for (int j = 1; j <= N; j++) {
        for (int c = N; c >= 1; c--) {
            if (c+j <= N && CellJmp[c+j][j] != BIGG) {
                int totalCost = CellJmp[c+j][j] + costs[c];
                if (totalCost < CellJmp[c][j])
                    CellJmp[c][j] = totalCost;
            }
            if (c-j >= 1 && CellJmp[c-j][j-1] != BIGG) {
                int totalCost = CellJmp[c-j][j-1] + costs[c];
                if (totalCost < CellJmp[c][j])
                    CellJmp[c][j] = totalCost;
            }
        }
    }
    int cheapest = BIGG;
    for (auto & c : CellJmp[N]) if (c < cheapest) cheapest = c;
    cout << cheapest << endl;
    return 0;
}
