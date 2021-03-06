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
    map<ull, int> picks;
    vi pick(5,0);
    cin >> N;
    while (N--) {
        for (int i = 0; i < 5; i++) {
            cin >> pick[i];
        }
        sort(pick.begin(), pick.end());
        ull pickUll = 0;
        for (int i = 0; i < 5; i++) {
            pickUll = pickUll*500 + pick[i];
        }
        picks[pickUll]++;
    }
    int max = 0, count = 0;
    for (auto& it : picks) {
        if (it.second > max) {
            max = it.second;
            count = it.second;
        } else if (it.second == max) {
            count += it.second;
        }
    }

    std::cout << count << std::endl;
    return 0;
}
