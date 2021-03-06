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
    int N,x;
    while (cin >> N) {
        if (N == 0) break;
        priority_queue<ull, vector<ull>, greater<ull>> nums;
        while (N--) {
            cin >> x;
            nums.push(x);
        }
        ull cost = 0;
        while(nums.size() > 1) {
            ull a = nums.top(); nums.pop();
            ull b = nums.top(); nums.pop();
            ull ab = a+b;
            cost += ab;
            nums.push(ab);
        }
        std::cout << cost << std::endl;
    }
    return 0;
}
