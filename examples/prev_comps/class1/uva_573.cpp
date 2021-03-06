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
    int H,U,D,F;
    while (true) {
        cin >> H >> U >> D >> F;
        if (H == 0) break;

        double spot = 0, tiring = (0.01 * F) * U, speed = U;
        int day = 1;

        while (true) {
            spot += speed;
            if (spot > H) {
                cout << "success on day " << day << endl;
                break;
            }
            spot -= D;
            if (spot < 0) {
                cout << "failure on day " << day << endl;
                break;
            }
            day++;
            speed -= tiring;
            if (speed < 0) speed = 0;
        }
    }

    return 0;
}
