#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<vu> vvu;

vu vecmatmul(const vu &A, const vvu &B, int mod) {
    int m = B.size(), l = B[0].size();
    vu C(l);
    for (int i = 0; i < l; i++) {
        ull sum = 0;
        for (int x = 0; x < m; x++) sum = (sum + A[x]*B[x][i]) % mod;
        C[i] = sum;
    }
    return C;
}

vvu matmul(const vvu &A, const vvu &B, int mod) {
    int n = A.size();
    vvu C(n);
    for (int i = 0; i < n; i++) C[i] = vecmatmul(A[i], B, mod);
    return C;
}

vvu matpow(vvu A, int pow, int mod) {
    int n = A.size();
    vvu C(n); for (int i = 0; i < n; i++) { C[i] = vu(n, 0); C[i][i] = 1; } // I
    while (pow) {
        if (pow & 1) C = matmul(C, A, mod);
        A = matmul(A, A, mod);
        pow >>= 1;
    }
    return C;
}

vu rotmatmul(const vu &A, const vu &B, int mod) {
    int n = A.size();
    vu C(n);
    for (int i = 0; i < n; i++) {
        ull sum = 0;
        for (int x = 0; x < n; x++) sum = (sum + A[x]*B[(n-x+i)%n]) % mod;
        C[i] = sum;
    }
    return C;
}

vu rotmatpow(vu A, int pow, int mod) {
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
    int T, n,S,L,R,X;
    cin >> T;
    while (T--) {
        cin >> n >> S >> L >> R >> X;
        vu nums(n);
        for (int i = 0; i < n; i++) cin >> nums[i];
        vu A(n, 0);
        A[0] = 1;
        A[1] = L;
        A[n-1] = R;

        int mod = 1; for(int i = 0; i < X; i++) mod *= 10;
        nums = vecmatmul(nums, rot2mat(rotmatpow(A, S, mod)), mod);
        for (int i = 0; i < n-1; i++)
            cout << nums[i] << " ";
        cout << nums[n-1] << endl;
    }

    return 0;
}
