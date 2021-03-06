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
typedef vector<ull> vu;
typedef vector<double> vd;

typedef pair<int, int> pii;
typedef pair<ull, ull> puu;
typedef pair<double, double> pdd;

typedef vector<pii> vii;
typedef vector<puu> vuu;
typedef vector<pdd> vdd;

typedef vector<vi> vvi;
typedef vector<vu> vvu;
typedef vector<vd> vvd;

typedef vector<vii> vvii;
typedef vector<vuu> vvuu;
typedef vector<vdd> vvdd;

struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};


char getFib(ull N, ull K, const vu& fibs) {
    if (N <= 2) {
        if (N == 1) return 'N';
        if (N == 2) return 'A';
    }

    ll n = fibs.size() - 2;

    while (n > 0) {
        if (K  > fibs[n]) {
            K -= fibs[n];
            n--;
        } else {
            n-=2;
        }
    }
    if ((n == 0 && K == 1)) return 'N';
    else return 'A';
}


int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
//	string h = "Hello";
//	cout << h.substr(1,7) << endl;
/*
    cout << 'N' << endl << 'A' << endl;
    ull a=1,b=1;
    vu fibs; fibs.push_back(a); fibs.push_back(b);
    for (int n = 3; n < 9; n++) {
        cout << "starting: " << n << endl;
        ull t = a;
        a = b;
        b = t+b;
        for (int k = 1; k <= b; k++) {
            cout << getFib(n, k, fibs);
        }
        cout << endl;
        fibs.push_back(b);
    }
    return 0;
*/
    ull N,K;
	cin >> N >> K;

    if (N <= 2) {
        cout << ((N==1) ? "N" : "A") << endl;
        return 0;
    }

	ull a=1,b=1;
    vu fibs; fibs.push_back(a); fibs.push_back(b);
    for (int i = 3; i < N; i++) {
        ull t = a;
        a = b;
        b = t+b;
        fibs.push_back(b);
        if (b > 1e18 && i%2 == N%2) break;
    }
    ll n = fibs.size() - 2;

	while (n > 0) {
        if (K  > fibs[n]) {
            K -= fibs[n];
            n--;
        } else {
            n-=2;
        }
	}
	if ((n == 0 && K == 1)) cout << "N" << endl;
	else cout << "A" << endl;
//    if (n == 0)
    // if (K == 1) "N" else "A";
	return 0;
}
