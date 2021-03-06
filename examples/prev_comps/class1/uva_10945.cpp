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
    string s;
    while(true) {
        getline(cin, s);
        s.erase(std::remove_if(s.begin(), s.end(),
                               []( int const& c ) -> bool { return !std::isalpha(c); } ), s.end());
        if (s == "DONE") break;
        int n = s.length();
        int st = 0, en = n-1;
        while (st < en) {
            if (toupper(s[st]) != toupper(s[en])) break;
            st++;
            en--;
        }
        if (st >= en) {
            cout << "You won't be eaten!" << endl;
        } else {
            cout << "Uh oh.." << endl;
        }
    }
    return 0;
}
