// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

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
typedef set<unsigned long> si;
typedef vector<si> vsi;

long long memo[101][101][101][2];

long long solve(int M, int d, int descent, int v){
    if(memo[M][d][v][descent] != -1){
        return memo[M][d][v][descent];
    } else {
        int count = 0;
        if(descent == 1){
            if(M==0) {
                if(v!=0)
                    return 0;
                return d;
            }
            for (int i = 0; i < d; ++i) {
                if(v!=0)
                    count += solve(M-1,i,1,v-1);
                count%= 1001113;
                count += solve(M-1,i,0,v);
                count%= 1001113;
            }
        }
        if(descent == 0){
            if(M==0) {
                if(v!=0)
                    return 0;
                return M - d + 1;
            }
            for (int i = d; i <= M; ++i) {
                if(v!=0)
                    count += solve(M-1,i,1,v-1);
                count%= 1001113;
                count += solve(M-1,i,0,v);
                count%= 1001113;
            }
        }
        return memo[M][d][v][descent] = count % 1001113;

    }
}


int main() {
    int n;
    cin >> n;
    for (int j = 0; j < 101; ++j) {
        for (int k = 0; k < 101; ++k) {
            for (int l = 0; l < 101; ++l) {
                memo[j][k][l][0] = -1;
                memo[j][k][l][1] = -1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int useless, N, v;
        cin >> useless >> N >> v;

        long long x = solve(N-1,N,1,v);
        printf("%d %lld\n", i+1, x);
    }


}