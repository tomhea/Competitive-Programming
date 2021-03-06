#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
typedef vector<double> vd;
typedef vector<vd> vvd;


#define INF 1e18
#define MAX 4004
// Most of the code was written through class8 competition, and minor bugs fixed later. Team c+++. 

vvd memo;
int N,L,W, ps[MAX];
double jump;

double f(int l, int r) {
    double &curr = memo[l][r];
    if (curr != INF) return curr;
    if (l == 0 && r == 0) return curr = 0;
    double d0 = abs(ps[l+r-1]-(l-1)*jump), d1 = abs(ps[l+r-1]-(r-1)*jump);
    if (l > 0) curr = min(curr, f(l-1,r) + d0);
    if (r > 0) curr = min(curr, f(l,r-1) + sqrt(d1*d1 + W*W));
    return curr;
}

int main() {
    while (cin >> N >> L >> W) {
        for (int i = 0; i < N; i++) cin >> ps[i];
        sort(ps, ps + N);

        int m = N / 2;
        jump = double(L) / (m - 1);
        memo = vvd(m + 1, vd(m + 1, INF));

        cout << setprecision(15) << fixed << f(m, m) << endl;
    }
    return 0;
}
