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
#include <unordered_map>
#include <numeric>
#include <iomanip>
#include <bits/stdc++.h>
#define loop(x,n) for(int x=0; x < n; ++x)
#define times(x) loop(__##x,x)
#define EPS 1e-9
#define INF 1e9
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<pair<double, double>> vdd;

typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};

unordered_map<pair<int, bitset<100>>, double, hash_pair> memo;
unordered_map<pair<int, bitset<100>>, pair<int, bitset<100>>, hash_pair> pre;

int n;
unordered_map<string, int> places;
vdd locs;
vi res;
bitset<100> bits;

double dist(int i, int j){
    return (sqrt(pow(locs[i].first - locs[j].first, 2) + pow(locs[i].second - locs[j].second, 2)));
}

double f(int last, bitset<100> left) {
    if (memo.find({last, left}) != memo.end()) {
        return memo[{last, left}];   //already calculated
    }
    if (!left.any()) {
        return dist(last, places["home"]);   //if all visited - return home
    }
    double ans = INF;
    int ans_ind;
    bitset<100> ans_b;
    for (int i = 0; i < n; ++i) {
        if (left[i]) {
            bitset<100> bitemp = left;
            bitemp.reset(i);
            double tmp = f(i, bitemp) + dist(last, i);
            if (ans > tmp) {
                ans = tmp;
                ans_b = bitemp;
                ans_ind = i;
            }
        }
    }
    pre[{last, left}] = {ans_ind, ans_b};
    return memo[{last, left}] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    double x,y;
    string s;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; ++i) {
        cin >> s >> x >> y;
        places[s] = i;
        locs.push_back({x,y});
        names[i] = s;
    }
    string line;
    string place;
    getline(cin,line);
    while(getline(cin,line)){
        bits.reset();
        stringstream ss(line);
        while (ss >> place){
            bits.set(places[place]);
        }
        pre.clear();
        res.clear();
        memo.clear();
        f(places["work"], bits);
        pair<int, bitset<100>> cur = {places["work"], bits};
        pair<int, bitset<100>> next;
        bool first = true;
        while (pre.find(cur) != pre.end()){
            next = pre[cur];
            if (!first) {
                cout << " ";
            }
            cout << names[next.first];
            first = false;
            cur = next;
        }
        cout << endl;
    }

    return 0;
}
