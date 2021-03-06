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
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int w,l,r,c;
        cin >> w >> l >> r >> c;
        int a1,a2,b1,b2;
        a1 = r;
        b1 = c;
        a2 = w-r-1;
        b2 = l-c-1;
        int res = a1^a2^b1^b2;
        if(res != 0)
            printf("Gretel\n");
        else
            printf("Hansel\n");
    }


    return 0;
}
