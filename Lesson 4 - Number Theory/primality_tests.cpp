#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

#define TIMER high_resolution_clock::now()

typedef long long ll;
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
//    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
//    for(ll a: dtrm_set){
//        if(a >= n) break;
        /* !!! End of deterministic version !!! */

        /* !!! Probablistic version !!! */
    while(k--){
        ll a = rand() % (n-4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a,m,n);
        if(a==1) continue;
        int i = r;
        while(i-- && a != n-1){
            a = mulmodn(a,a,n);
            if(a == 1) return false;
        }
        if(i == -1) return false;
    }
    return true;
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

vector<bool> sieve(int n){
    vector<bool> ps(n+1,true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if(ps[i]){
            for (int j = i*i; j <= n; j+=i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}


int main() {
    srand(time(NULL));
    int c = 0;
    int n =  10000;
    cout << "Check up to sqrt(n):" << endl;
    auto start = TIMER;
    for (int i = 2; i < n; ++i) {
        if(isPrime(i)){
            c+=1;
        }
    }
    cout << "There are " << c << " prime numbers below " << n << endl;
    cout << "Exec time: " << duration_cast<microseconds>(TIMER - start).count()/1000000.0 << endl << endl;

    cout<< "Miller-Rabin:" << endl;
    c = 0;
    start = TIMER;
    for (int i = 2; i < n; ++i) {
        if(MR(i)){
            c+=1;
        }
    }
    cout << "There are " << c << " prime numbers below " << n << endl;
    cout << "Exec time: " << duration_cast<microseconds>(TIMER - start).count()/1000000.0 << endl << endl;

    cout<< "Sieve:" << endl;
    c = 0;
    start = TIMER;
    for (auto p : sieve(n)) {
        if(p){
            c+=1;
        }
    }
    cout << "There are " << c << " prime numbers below " << n << endl;
    cout << "Exec time: " << duration_cast<microseconds>(TIMER - start).count()/1000000.0 << endl << endl;
    return 0;
}