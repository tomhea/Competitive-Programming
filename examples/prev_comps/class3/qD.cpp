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


int main() {
    int W, P;
    cin >> W >> P;
    vi e;
    e.push_back(0);
    e.push_back(W);
    int X;
    while (P--) {
        cin >> X;
        e.push_back(X);
    }
    sort(e.begin(), e.end());
    vi sizes;

    for (int x : e) {
        for (int y : e) {
            int w = abs(y-x);
            if (w == 0) continue;
            bool found = false;
            for (int z : sizes) {
                if (z == w) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                sizes.push_back(w);
            }
        }
    }
    sort(sizes.begin(), sizes.end());
    for (int size : sizes) {
        cout << size << " ";
    }
    cout << endl;

    return 0;
}
