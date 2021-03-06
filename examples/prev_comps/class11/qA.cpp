#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<vl> vvl;

vl vecmatmul(const vl &A, const vvl &B, ull mod) {
    int m = B.size(), l = B[0].size();
    vl C(l);
    for (int i = 0; i < l; i++) {
        ll sum = 0;
        for (int x = 0; x < m; x++) sum = (sum + A[x]*B[x][i]) % mod;
        C[i] = sum;
    }
    return C;
}

vvl matmul(const vvl &A, const vvl &B, ull mod) {
    int n = A.size();
    vvl C(n);
    for (int i = 0; i < n; i++) C[i] = vecmatmul(A[i], B, mod);
    return C;
}

vvl matpow(vvl A, ull pow, ull mod) {
    int n = A.size();
    vvl C(n); for (int i = 0; i < n; i++) { C[i] = vl(n, 0); C[i][i] = 1; } // I
    while (pow) {
        if (pow & 1) C = matmul(C, A, mod);
        A = matmul(A, A, mod);
        pow >>= 1;
    }
    return C;
}

vl rotmatmul(const vl &A, const vl &B, ull mod) {
    int n = A.size();
    vl C(n);
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int x = 0; x < n; x++) sum = (sum + A[x]*B[(n-x+i)%n]) % mod;
        C[i] = sum;
    }
    return C;
}

vl rotmatpow(vl A, ull pow, ull mod) {
    int n = A.size();
    vl C(n, 0); C[0] = 1;  // I
    while (pow) {
        if (pow & 1) C = rotmatmul(C, A, mod);
        A = rotmatmul(A, A, mod);
        pow >>= 1;
    }
    return C;
}

vvl rot2mat(const vl &A) {
    int n = A.size();
    vvl C(n);
    for (int i = 0; i < n; i++) {
        C[i] = vl(n);
        for (int j = 0; j < n; j++)
            C[i][j] = A[(j-i+n)%n];
    }
    return C;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    ll N,Q, T,M;
    cin >> N;
    vvl At(N+1, vl(N+1));
    At[0][0] = 1; for (int i = 1; i <= N; i++) At[i][0] = 0;
    vl a(N+1); for (int i = 0; i <= N; i++) cin >> a[i];
    for (int i = 2; i <= N; i++) for (int j = 0; j <= N; j++) At[j][i] = (j == i-1);
    vl v(N+1); v[0] = 1; for (int i = 0; i < N; i++) cin >> v[N-i];

    cin >> Q;
    while (Q--) {
        cin >> T >> M;
        vl v_mod(N+1);  for (int i = 0; i <= N; i++) v_mod[i] = ((v[i]%M)+M)%M;
        for (int i = 0; i <= N; i++) At[i][1] = ((a[i]%M)+M)%M;
        cout << vecmatmul(v_mod, matpow(At, T, M), M)[N] << endl;
    }

    return 0;
}
