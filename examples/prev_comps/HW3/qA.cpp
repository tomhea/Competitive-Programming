#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define BIG_MOD 1000000007

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


int r2int(int* r) {
    int x = 0;
    for (int i = 0; i < 4; i++) {
        x = x*7 + r[i];
    }
    return x;
}

map<int,int> initInt2c() {
    map<int, int> int2c;
    int c = 0;
    for (int r1 = 0; r1 < 7; r1++) {
        for (int r2 = r1 + 1; r2 < 7; r2++) {
            for (int r3 = r2 + 1; r3 < 7; r3++) {
                for (int r4 = r3 + 1; r4 < 7; r4++) {
                    int r[4] = {r1, r2, r3, r4};
                    int2c[r2int(r)] = c++;
                }
            }
        }
    }
    return int2c;
}

vvl R(35);

void initR(map<int,int> int2c) {
    for (int r1 = 0; r1 < 7; r1++) {
        for (int r2 = r1+1; r2 < 7; r2++) {
            for (int r3 = r2+1; r3 < 7; r3++) {
                for (int r4 = r3+1; r4 < 7; r4++) {
                    int r[4] = {r1,r2,r3,r4};
                    int c = int2c[r2int(r)];
                    R[c] = vl(35, 0);
                    for (int m = 0b0000; m <= 0b1111; m++) {
                        int l[7] = {0};
                        int new_r[4];
                        bool bad = false;
                        for (int i = 0; i < 4; i++) {
                            new_r[i] = r[i] + ((m & (1<<i)) ? 1 : -1);
                        }
                        for (int i = 0; i < 4; i++) {
                            if (new_r[i] < 0 || new_r[i] >= 7) {
                                bad = true;
                                break;
                            }
                            for (int j = i+1; j < 4; j++) {
                                if (new_r[i] == new_r[j]) {
                                    bad = true;
                                    break;
                                }
                            }
                        }
                        if (!bad) {
                            sort(new_r, new_r+4);
                            R[c][int2c[r2int(new_r)]] = 1;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int T, N;
    int r[4];
    map<int, int> int2c = initInt2c();
    cin >> T;
    while (T--) {
        initR(int2c);
        cin >> N; N--;
        int temp, temp_i = 0;
        for (int i = 0; i < 7; i++) {
            cin >> temp;
            if (temp > 0) {
                r[temp_i++] = i;
            }
        }
        vl v(35, 0);
        v[int2c[r2int(r)]] = 1;
        vl ans = vecmatmul(v, matpow(R, N, BIG_MOD), BIG_MOD);
        ll sum = 0;
        for (int i = 0; i < 35; i++) {
            sum = (sum + ans[i]) % BIG_MOD;
        }
        cout << sum << endl;
    }

    return 0;
}
