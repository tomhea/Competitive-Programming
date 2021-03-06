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


bool chrStrongCmp(int a, int b) {
    a = 2*tolower(a) + (islower(a)!=0);
    b = 2*tolower(b) + (islower(b)!=0);
    return a < b;
}

int main() {
    vector<string> outputWords;
    int N;
    string s;
    cin >> N;
    while (N--) {
        outputWords.clear();
        cin >> s;
        sort(s.begin(), s.end(), chrStrongCmp);
        do {
            cout << s << endl;
        } while (next_permutation(s.begin(), s.end(), chrStrongCmp));
    }
    return 0;
}
