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


struct unionfind{vector<int> rank;vector<int> parent;unionfind(int size)    {rank=vector<int>(size,0);parent=vector<int>(size);for(int i=0;i<size;i++)parent[i]=i;}int find(int x){int tmp=x;while(x!=parent[x]) x=parent[x];while(tmp!=x)       {int remember=parent[tmp];parent[tmp]=x;tmp=remember; } return x;}void Union(int p, int q){p = find(p);q = find(q);if(q==p){return;}if(rank[p] < rank[q]) parent[p] = q;else parent[q] = p;if(rank[p] == rank[q]) rank[p]++;}};



int main() {
    int N, n, m, p,q;
    cin >> n >> m;
    N=n;
    unionfind groups(n);
    vector<int> owes;
    while (n--) {
        cin >> p;
        owes.push_back(p);
    }
    while (m--) {
        cin >> p >> q;
        groups.Union(p, q);
    }
    bool possible = true;
    for (int i = 0; i < N; i++) {
        int sum = 0;
        int i_group = groups.find(i);
        for (int j = 0; j < N; j++) {
            if (groups.find(j) == i_group) {
                sum += owes[j];
            }
        }
        if (sum != 0) {
            possible = false;
            break;
        }
    }
    if (possible) {
        cout << "POSSIBLE" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
