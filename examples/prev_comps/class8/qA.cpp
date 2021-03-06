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
typedef vector<short> vi;
typedef pair<int, int> pii;

int values[201][201][3];
bool flags[201][201][3];


int fv(int gallery[200][2],int k,int l,int close) {
    if(l==0) {
        if(k>=1) {
            values[l][k][close + 1] = 0;
            flags[l][k][close + 1] = false;
            return 0;
        }
        flags[l][k][close + 1] = true;
        if(close == 0)
            values[l][k][close + 1] = gallery[l][0] + gallery[l][1];
        else if(close == 1)
            values[l][k][close + 1] = gallery[l][0];
        else if(close == -1)
            values[l][k][close + 1] = gallery[l][1];
        return values[l][k][close + 1];
    }
    if(values[l][k][close+1] != -1)
        return values[l][k][close+1];

    int value = 0;
    bool flag = false;
    if(close == 0) {
        value = gallery[l][0] + gallery[l][1];
        int x = 0;
        int temp = 0;
        temp = fv(gallery,k,l-1,0);
        if(flags[l-1][k][1]){
            x = max(x,temp);
            flag = true;
        }
        if(k>0) {
            temp = fv(gallery, k - 1, l - 1, 1);
            if(flags[l-1][k-1][2]){
                x = max(x,temp);
                flag = true;
            }
            temp = fv(gallery, k - 1, l - 1, -1);
            if(flags[l-1][k-1][0]){
                x = max(x,temp);
                flag = true;
            }
        }
        value += x;
    }
    if(close == 1) {
        value = gallery[l][0];
        int x = 0;
        int temp = 0;
        temp = fv(gallery,k,l-1,0);
        if(flags[l-1][k][1]){
            x = max(x,temp);
            flag = true;
        }
        if(k>0) {
            temp = fv(gallery, k - 1, l - 1, 1);
            if (flags[l - 1][k-1][ 2]) {
                x = max(x, temp);
                flag = true;
            }
        }
        value += x;
    }
    if(close == -1) {
        value = gallery[l][1];
        int x = 0;
        int temp = 0;
        temp = fv(gallery,k,l-1,0);
        if(flags[l-1][k][1]){
            x = max(x,temp);
            flag = true;
        }
        if(k>0) {
            temp = fv(gallery, k - 1, l - 1, -1);
            if(flags[l-1][k-1][0]){
                x = max(x,temp);
                flag = true;
            }
        }
        value += x;
    }
    if(!flag)
        value = 0;
    values[l][k][close+1] = value;
    flags[l][k][close+1] = flag;
    return value;
}


int f(int gallery[200][2],int k,int l) {
    int value = 0;
    value = max(fv(gallery, k, l - 1, 0), value);
    if (k > 0) {
        value = max(fv(gallery, k - 1, l - 1, 1), value);
        value = max(fv(gallery, k - 1, l - 1, -1), value);

    }
    return value;
}

int main() {
    while(true) {
        int n, k;
        cin >> n >> k;
        if(n == 0 && k ==0){
            break;
        }
        for (int j = 0; j < n+1; ++j) {
            for (int i = 0; i < k+1; ++i) {
                values[j][i][0] = -1;
                values[j][i][1] = -1;
                values[j][i][2] = -1;
            }
        }
        int gallery[200][2];
        for (int i = 0; i < n; ++i) {
            cin >> gallery[i][0] >> gallery[i][1];
        }

        int value = f(gallery,k,n);
        cout << value << endl;

    }
}