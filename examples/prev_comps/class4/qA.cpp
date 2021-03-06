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
typedef pair<int, int> pii;

int main() {
    string nf;
    cin >> nf;
    int N = nf.size(), n = 1;
    double nd=0,semiNF = N-1 + log10(nf[0]-'0');     // close to but smaller then log10(nf)
    while (nd < semiNF)
        nd += log10(++n);
    cout << n << endl;
    return 0;
}
