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
    int N, T, c, t;
    cin >> N >> T;
    vi cc, tt;
    int n = N;
    while (N--) {
        cin >> c >> t;
        cc.push_back(c);
        tt.push_back(t);
    }
    int M=0;
    while(T--) {
        if (n == 0) {
//            T--;
            continue;
        }
        int max=-1, maxI=0;
        for (int i = 0; i < n; i++) {
            if (tt[i] >= T) {
                if (cc[i] > max) {
                    max = cc[i];
                    maxI = i;
                }
            }
        }
        if (max == -1) {
//            T--;
            continue;
        }
        cc[maxI] = cc[n-1];
        cc.pop_back();
        tt[maxI] = tt[n-1];
        tt.pop_back();
        n--;
        M += max;

//        T--;
    }


    std::cout << M << std::endl;
    return 0;
}
