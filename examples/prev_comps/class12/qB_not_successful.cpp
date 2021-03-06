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
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<ull> vu;
typedef vector<double> vd;

typedef pair<int, int> pii;
typedef pair<ull, ull> puu;
typedef pair<double, double> pdd;

typedef vector<pii> vii;
typedef vector<puu> vuu;
typedef vector<pdd> vdd;

typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vb> vvb;
typedef vector<vu> vvu;
typedef vector<vd> vvd;

typedef vector<vii> vvii;
typedef vector<vuu> vvuu;
typedef vector<vdd> vvdd;

struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};


string reduceCircles(string s) {
    int n = s.size();
    for (int i = 1; i < n; i++) {
        if (n % i != 0) continue;
        bool is_loop = true;
        for (int j = 0; j < i; j++) {
            for (int k = i+j; k < n; k += i) {
                if (s[j] != s[k]) is_loop = false;
            }
        }
        if (is_loop) {
            return s.substr(0, i);
        }
    }
    return s;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int N,n;
    cin >> N;
    string ops, boardLine;
    cin >> ops;
    ops = reduceCircles(ops);
    n = ops.size();
    int x,y;
    vvb board(N, vb(N)); // false tile means it impossible to be on it
    for (int i = 0; i < N; i++) {
        cin >> boardLine;
        for (int j = 0; j < N; j++) {
            if (boardLine[j] == 'R') { x = i; y = j; }
            board[i][j] = (boardLine[j] != '#');
        }
    }
    vvvi hist(n, vvi(N, vi(N, -1)));

    int counter = 0, i;
    bool cont = true;
    while (cont) {
        for (i = 0; i < n; i++) {
            int& h = hist[i][y][x];
            if (h > 0) { cont = false; break; }
//            if (counter++ > N*N*n) { cont = false; break; }
            h = counter;
            if (ops[i] == '<') if (board[y][x - 1]) { counter++; x--; }
            if (ops[i] == '>') if (board[y][x + 1]) { counter++; x++; }
            if (ops[i] == '^') if (board[y - 1][x]) { counter++; y--; }
            if (ops[i] == 'v') if (board[y + 1][x]) { counter++; y++; }
        }
    }
//    n = counter - hist[i][y][x];
//    if (verify == 0) verify = 1;
//    cout << n << endl;
    string actual = "";
    vi xs, ys;
    for (int j = i; j < i + n; j++) {
        if (ops[j%n] == '<') if (board[y][x-1]) { actual += '<'; x--; xs.push_back(x); ys.push_back(y); }
        if (ops[j%n] == '>') if (board[y][x+1]) { actual += '>'; x++; xs.push_back(x); ys.push_back(y); }
        if (ops[j%n] == '^') if (board[y-1][x]) { actual += '^'; y--; xs.push_back(x); ys.push_back(y); }
        if (ops[j%n] == 'v') if (board[y+1][x]) { actual += 'v'; y++; xs.push_back(x); ys.push_back(y); }
    }

    actual = reduceCircles(actual);
    int actual_len = actual.size();
    if (actual_len == 0) actual_len = 1;
    cout << actual_len << endl;

    /*
    n = actual.size();
//    cout << n << endl;
    if (n == 0 || n == 1) {
        cout << 1 << endl;
        return 0;
    }
    else {
        for (i = 1; i < n; i++) {
            if (n % i != 0) continue;
            bool is_loop = true;
            for (int j = 0; j < i; j++) {
                for (int k = i+j; k < n; k += i) {
                    if (actual[j] != actual[k]) is_loop = false;
                }
            }
            if (is_loop) {
                cout << i << endl;
                return 0;
            }
        }
    }
    cout << n << endl;
     */
    return 0;
}
