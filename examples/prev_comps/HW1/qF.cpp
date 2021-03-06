#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
using namespace std;

ll mulmodn(ll a, ll b, ll n){
    ll res = 0;
    while(b){
        if(b & 1) res= (res+a) %n;
        a = (a*2)%n;
        b >>= 1;
    }
    return res;
}

ll powmodn(ll a, ll q, ll n){
    ll res = 1;
    while(q){
        if (q & 1) res = mulmodn(res,a,n);
        a = mulmodn(a,a,n);
        q >>= 1;
    }
    return res;
}

bool isPrime(ll n){
    if(n<2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if(n%i == 0){
            return false;
        }
    }
    return true;
}

int main() {
    int p,a;
    while (cin >> p >> a) {
        if (p == 0 && a == 0) break;
        if (!isPrime(p) && powmodn(a,p,p) == a) {
            cout << "yes" << endl;
        } else {
            cout << "no"  << endl;
        }
    }
    return 0;
}
