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
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>
#define times(x) int _##x = x; while(_##x--)
#define loop(x,n) int x=0; for(; x < n; ++x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
bool MR(ll, int);
bool isPrime(ll n);


vector<string> v;

int main() {
    int n;
    string x;
    cin >> n;
    times(n){
        cin >> x;
        v.push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        int count = 0;
        int prime_count = 0;
        string s = v[i];
        const char *c = s.c_str();
        char* p = NULL;
        ll val = strtol(c, &p, 2);
        if (p - c == s.size()){
            count++;
//            if (val > 0 && MR(val, 5)) prime_count++;
            if (val > 0 && isPrime(val)) prime_count++;
        }
        val = strtol(c, &p, 8);
        if (p - c == s.size()){
            count++;
//            if (val > 0 && MR(val, 5)) prime_count++;
            if (val > 0 && isPrime(val)) prime_count++;

        }
        val = strtol(c, &p, 10);
        if (p - c == s.size()){
            count++;
//            if (val > 0 && MR(val, 5)) prime_count++;
            if (val > 0 && isPrime(val)) prime_count++;

        }
        val = strtol(c, &p, 16);
        if (p - c == s.size()){
            count++;
//            if (val > 0 && MR(val, 5)) prime_count++;
            if (val > 0 && isPrime(val)) prime_count++;

        }

        if(prime_count == 0 || count ==0){
            cout << "0/1" << endl;
        } else{
            int g = __gcd(prime_count, count);
            int lcd = (g!=0)?(prime_count*count)/g : 0;
            cout << lcd/count << "/" << lcd/prime_count << endl;
        }
    }
    return 0;
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

ll powmodn(ll a, ll q, ll n){
    ll res = 1;
    while(q){
        if (q%2) res = (res * a) % n;
        a = (a * a) % n;
        q >>= 1;
    }
    return res;
}

bool MR(ll n, int k=5){
    if(n==1 || n==4)
        return false;
    if(n==2 || n==3)
        return true;
    ll m = n - 1;
    int r = 0;
    while (m%2 == 0){
        m >>= 1;
        r+=1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for(ll a: dtrm_set){
        if(a >= n) break;
        /* !!! End of deterministic version !!! */

        /* !!! Probablistic version !!! */
//    while(k--){
//        ll a = rand() % (n-4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a,m,n);
        if(a==1) continue;
        int i = r;
        while(i-- && a != n-1){
            a = (a*a)%n;
            if(a == 1) return false;
        }
        if(i == -1) return false;
    }
    return true;
}