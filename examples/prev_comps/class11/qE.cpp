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

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<vu> vvu;

#define BIGMOD 1000000009

vu vecmatmul(const vu &A, const vvu &B, ull mod) {
    int m = B.size(), l = B[0].size();
    vu C(l);
    for (int i = 0; i < l; i++) {
        ull sum = 0;
        for (int x = 0; x < m; x++) sum = (sum + A[x]*B[x][i]) % mod;
        C[i] = sum;
    }
    return C;
}

vvu matmul(const vvu &A, const vvu &B, ull mod) {
    int n = A.size();
    vvu C(n);
    for (int i = 0; i < n; i++) C[i] = vecmatmul(A[i], B, mod);
    return C;
}

vvu matpow(vvu A, ull pow, ull mod) {
    int n = A.size();
    vvu C(n); for (int i = 0; i < n; i++) { C[i] = vu(n, 0); C[i][i] = 1; } // I
    while (pow) {
        if (pow & 1) C = matmul(C, A, mod);
        A = matmul(A, A, mod);
        pow >>= 1;
    }
    return C;
}

vu rotmatmul(const vu &A, const vu &B, ull mod) {
    int n = A.size();
    vu C(n);
    for (int i = 0; i < n; i++) {
        ull sum = 0;
        for (int x = 0; x < n; x++) sum = (sum + A[x]*B[(n-x+i)%n]) % mod;
        C[i] = sum;
    }
    return C;
}

vu rotmatpow(vu A, ull pow, ull mod) {
    int n = A.size();
    vu C(n, 0); C[0] = 1;  // I
    while (pow) {
        if (pow & 1) C = rotmatmul(C, A, mod);
        A = rotmatmul(A, A, mod);
        pow >>= 1;
    }
    return C;
}

vvu rot2mat(const vu &A) {
    int n = A.size();
    vvu C(n);
    for (int i = 0; i < n; i++) {
        C[i] = vu(n);
        for (int j = 0; j < n; j++)
            C[i][j] = A[(j-i+n)%n];
    }
    return C;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

//    vvu A  = {{1,1,1}, {1,0,0}, {0,1,0}};
    vvu At = {{1,1,0}, {1,0,1}, {1,0,0}};
    vu  v  =  {2,1,0};

    ull n;
    while (cin >> n) {
        if (n == 0) break;
        cout << vecmatmul(v, matpow(At, n-1, BIGMOD), BIGMOD)[2] << endl;
    }

    return 0;
}
