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
    vector<string> words;
    string word;
    while(true) {
        cin >> word;
        if (word == "#") break;
        words.push_back(word);
    }
    sort(words.begin(), words.end());
    vector<string> swords;
    for (auto& w : words) {
        string sw = w;
        transform(sw.begin(), sw.end(), sw.begin(), [](char c){return tolower(c);});
        sort(sw.begin(), sw.end());
        swords.push_back(sw);
    }
    int n = words.size();
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (auto& w : swords)
            if (swords[i] == w)
                count++;
        if (count == 1)
            cout << words[i] << endl;
    }
    return 0;
}
