#include <algorithm>
#include <iostream>
#include <vector>
#define times(x) int __##x = x; while(__##x--)
using namespace std;
typedef pair<int, int> pii;

int main() {
    int n, a, b, x, g, lcd;
    vector<int> v;
    cin >> n;
    times(n){
        cin >> x;
        v.push_back(x);
    }
    a = v[0];
    for (int i = 1; i < n; ++i) {
        b = v[i];
        g = __gcd(a, b);
        lcd = (a*b)/g;
        cout << lcd/b << "/" << lcd/a << endl;
//        a = b;
    }
    return 0;
}
