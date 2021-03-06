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

#define EPS 1e-7

double getHeight(vi H, vi T, bool up, double time) {
    double h = 0, t = 0;
    if (!up) for (int dh : H) h += -dh;
    if (time == 0) return h;
    for (int i = 0; i < H.size(); i++) {
        double dh = H[i];
        double dt = T[i];
        if (t + dt >= time) {
            double ds = dh/dt;
            dt = time - t;
            h += ds*dt;
            return h;
        }

        h += dh;
        t += dt;
    }
    return h;
}

int main() {
    int a, d, h, t;
    vi upH, upT, downH, downT;
    cin >> a >> d;
    double tUpEnd=0,tDownEnd=0;
    while (a--) {
        cin >> h >> t;
        upH.push_back(h);
        upT.push_back(t);
        tUpEnd += t;
    }
    while (d--) {
        cin >> h >> t;
        downH.push_back(-h);
        downT.push_back(t);
        tDownEnd += t;
    }

    double tStart=0, tEnd=min(tUpEnd, tDownEnd);
    double tMid = (tStart+tEnd)/2.0;
    //double h1, h2;
    while (tEnd-tStart > EPS) {
        tMid = (tStart+tEnd)/2.0;
        double h1 = getHeight(upH  , upT  , true , tMid);
        double h2 = getHeight(downH, downT, false, tMid);
        if (h2 > h1) tStart = tMid;
        else tEnd = tMid;
    }
    cout << tMid << endl;
}
