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
    int times;
    cin >> times;
    while(times--) {
        ll shop, max=0, min=0;
        int shops;
        cin >> shops;
        for (int i = 0; i < shops; i++) {
            cin >> shop;
            if (i == 0) {
                min = shop;
                max = shop;
            }
            if (shop < min) min = shop;
            if (shop > max) max = shop;
        }
        cout << (max-min)*2 << endl;
    }
    return 0;
}
