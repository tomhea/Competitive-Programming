#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

vvi memo;
int cleanLine(vi &line, int s, int e) {
    if (s > e) return 0;
    int& mem = memo[s][e];
    if (mem != -1) return mem;
    if (s == e) return mem = 1;

    int min_cost = 1 + cleanLine(line, s+1, e);
    for (int i = s+1; i <= e; i++) {
        if (line[i] != line[s]) continue;
        int left  = cleanLine(line, s+1, i-1);
        int right = cleanLine(line, i, e);
        min_cost = min(min_cost, left + right);
    }
    return mem = min_cost;
}

int main() {
    int T, N;
    cin >> T;
    for (int test_i = 1; test_i <= T; test_i++) {
        cin >> N;
        int c = 0;
        map<string,int> str2i;
        vvi lines(1);
        int lastLine = 0;
        string s;
        for (int i = 0; i < N; i++) {
            cin >> s;
            if (isupper(s[0])) {
                lines.push_back(vi(0));
                lastLine++;
            } else {
                if (str2i.find(s) == str2i.end()) str2i[s] = c++;
                int n = lines[lastLine].size();
                if (n == 0 || lines[lastLine][n-1] != str2i[s])
                    lines[lastLine].push_back(str2i[s]);
            }
        }
        int sumCost = 0;
        for (vi line : lines) {
            int n = line.size();
            memo = vvi(n, vi(n, -1));
            sumCost += cleanLine(line, 0, n-1);
        }
        printf("Case %d: %d\n", test_i, sumCost);
    }

    return 0;
}
