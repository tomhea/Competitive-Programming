#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define EPS 1e-6

double calcDist(int t, double r, int n, vector<pair<double, double>> speeds) {
    double k = t-r;
    double min, temp, s1,s2;
    for (int i = 0; i < n; i++) {
        s1 = speeds[i].first; s2 = speeds[i].second;
        temp = r/s1 + k/s2;
        if (i == n-1) return min - temp;
        if (i == 0 || temp < min) min = temp;
    }
    return 0;
}


int main() {
    int t,n;
    double s1,s2, r,k, winby;
    while (cin >> t >> n) {
        vector<pair<double, double>> speeds;
        speeds.clear();
        for (int i = 0; i < n; i++) {
            cin >> s1 >> s2;
            speeds.push_back({s1, s2});
        }

//        double l = 0, h = t, m1,m2;       // trinary search, very fast!
//        while (fabs(h-l) > EPS) {
//            m1 = (2*l+h)/3;
//            m2 = (l+2*h)/3;
//            if (calcDist(t,m1,n,speeds) > calcDist(t,m2,n,speeds)) h = m2;
//            else l = m1;
//        }
//        r = (m1 == l ? m2 : m1);

        r = 0;                              // brute-froce search, quite slow
        for (int i = 0; i <= 1000*t; i++)
            if (calcDist(t, i*0.001, n, speeds) > calcDist(t, r, n, speeds)) r = i*0.001;

        k = t - r;
        winby = calcDist(t,r,n,speeds);
        if (winby >= -EPS) {
            printf("The cheater can win by %.0f seconds with r = %.2fkm and k = %.2fkm.\n", fabs(winby*3600), fabs(r), fabs(k));
        } else {
            printf("The cheater cannot win.\n");
        }
    }

    return 0;
}
