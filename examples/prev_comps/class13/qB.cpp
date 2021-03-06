// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

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
typedef pair<int,int> ii;
typedef pair<ll,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

int main() {
    pair<int,int> mapping[9];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int m;
            cin >> m;
            mapping[m-1] = pair<int,int>(i,j);
        }
    }

    double sum = 0;
    for (int k = 0; k < 8; ++k) {
        double deltax = mapping[k].first-mapping[k+1].first;
        double deltay = mapping[k].second-mapping[k+1].second;
        sum += sqrt(deltax*deltax+deltay*deltay);
    }

    printf("%.8f\n",sum);


}