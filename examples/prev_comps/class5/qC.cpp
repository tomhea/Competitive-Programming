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
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<vector<pii>> vvii;


bool shouldLeave(const vvi& g, int L, int X) {
    vi indegree (g.size(), 0);
    for(int v=0; v<g.size(); v++) for(int u : g[v]) indegree[u]++;
    vi startingIndegree (g.size(), 0);
    for(int v=0; v<g.size(); v++) for(int u : g[v]) startingIndegree[u]++;

    vi leaving = vector<int>();
    indegree[L] = -1;
    leaving.push_back(L);

    for(int i=0; i < leaving.size(); i++) for(int u : g[leaving[i]]) if (indegree[u] != -1) {
        indegree[u]--;
        if(2 * indegree[u] <= startingIndegree[u]) {
            indegree[u] = -1;
            leaving.push_back(u);
        }
    }
    return find(leaving.begin(), leaving.end(), X) != leaving.end() ;
}


int main() {
    int C,P,X,L;
    cin >> C >> P >> X >> L; X--; L--;
    vvi g;
    while (C--) { vi neighbours; g.push_back(neighbours); }
    while (P--) {
        int a,b; cin >> a >> b; a--; b--;
        g[a].push_back(b); g[b].push_back(a);
    }
    if (shouldLeave(g,L,X)) {
        cout << "leave" << endl;
    } else {
        cout << "stay"  << endl;
    }

    return 0;
}
