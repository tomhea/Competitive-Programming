#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<double, double> pdd;
typedef vector<pdd> vdd;


pdd rotpoint(pdd p, double alpha) {
    double x = p.first, y = p.second;
    double s = sin(alpha), c = cos(alpha);
    return {x*c-y*s, x*s+y*c};
}

vdd rotpoly(const vdd &poly, double alpha) {
    vdd rot;
    for (auto& p : poly) rot.push_back(rotpoint(p, alpha));
    return rot;
}

double heightBound(vdd poly) {
    double miny,maxy; miny=maxy=poly[0].second;
    for (pdd p : poly) {
        double y = p.second;
        if (y<miny)miny=y;
        if (y>maxy)maxy=y;
    }
    return (maxy-miny);
}

int main() {
    int N, times=10000;
    double x,y, minS,alpha;
    cin >> N;
    vdd poly;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        poly.push_back({x, y});
    }

    minS = heightBound(rotpoly(poly, 0));
    for (int i = 0; i <= times; i++) {
        alpha = i/(double)times * M_PI;
        minS = min(minS, heightBound(rotpoly(poly, alpha)));
    }

    cout << minS << endl;
    return 0;
}
