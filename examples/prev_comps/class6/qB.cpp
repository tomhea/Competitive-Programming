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
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<vector<pii>> vvii;


int main() {
    int N;
    cin >> N;
    vector<ull> sticks(N);
    for(int i = 0; i < N;   i++) cin >> sticks[i];

    sort(sticks.begin(), sticks.end());
    for(int i = 0; i < N-2; i++) if (sticks[i]+sticks[i+1] > sticks[i+2]) { cout << "possible" << endl; return 0; }
    cout << "impossible" << endl;

    return 0;
}
