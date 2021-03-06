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


int cut_string(string s, int i) {
    return 0;
}


int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
//	string h = "Hello";
//	cout << h.substr(1,7) << endl;
	int N;
	cin >> N;
	while (N--) {
	    string s;
	    cin >> s;
	    int n = s.length();
	    vector<string> vs;

	    for (int i = 0; i < n; i++) {
	        vs.push_back(s.substr(i,n-i) + s.substr(0,i));
	    }
	    sort(vs.begin(), vs.end());
	    cout << vs[0] << endl;
	}

//    cout << "Hello, World!" << endl;
    return 0;
}
