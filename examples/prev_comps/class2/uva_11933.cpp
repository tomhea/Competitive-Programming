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
    int N;
    while (cin >> N) {
        if (N == 0) break;

        int a=0,b=0;
        bool aTurn=true;
        for (int i = 0; i < 31; i++) {
            if (N & (1 << i)) {
                if (aTurn)
                    a += (1 << i);
                else
                    b += (1 << i);
                aTurn = !aTurn;
            }
        }
        cout << a << " " << b << endl;
    }

    return 0;
}
