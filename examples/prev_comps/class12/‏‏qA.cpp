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
typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};
int wins[10000001];
int opt[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, x;
    while (cin >> n){
        memset(wins,0, 10000001);
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> opt[i];
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                if(i > opt[j]-1 && !wins[i - opt[j]]){
                    wins[i] = 1;
                    break;
                }
            }
        }
        if(wins[n] == 1){
            cout << "Stan wins"<< endl;
        } else{
            cout << "Ollie wins"<< endl;
        }
    }

    return 0;
}
