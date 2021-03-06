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


ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a/b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}


int main() {
    int n;
    cin >> n;
    for(int i = 0; i<n; i++){
        ll k,c;
        cin >> k >> c;
        ll a,b;
        if (k==1){
            if(c==1)
                printf("2\n");
            else
                printf("1\n");
            continue;
        }
        if (c==1){
            if (k+1 > 1000000000)
                printf("IMPOSSIBLE\n");
            else
                printf("%lld\n", k+1);
            continue;
        }
        ll d = extended_euclid(k, c, a, b);
        if (d > 1) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        if (b < 0)
            b = (k + (b%k)) % k;
        if (b>=1000000000){
            printf("IMPOSSIBLE\n");
            continue;
        }
        printf("%lld\n", b);
    }

}