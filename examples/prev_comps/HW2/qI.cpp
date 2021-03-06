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
ll dp[11][11];
int pre[11][11];
vi dims;
int num;

void print_res(int i, int j){
    int k = pre[i][j];
    if(k == -1) {
        if (j - i == 1){
            cout << "A" << num++;
        } else{
            cout << "(A" << num++ << " x A" << num++ << ")" ;
        }

    } else{
        cout << "(";
        print_res(i, k);
        cout << " x ";
        print_res(k, j);
        cout << ")";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x, y, count = 0;
    while ((cin >> n) && (n !=0)){
        count++;
        dims.clear();
        memset(dp, 0, sizeof(ll) * 11*11);
        memset(pre, -1, sizeof(int) * 11*11);
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            dims.push_back(x);
        }
        dims.push_back(y);
        for (int l = 0; l <= n-2; ++l) {
            dp[l][l+2] = dims[l]*dims[l+1]*dims[l+2];
        }

        for (int s = 3; s <= n; ++s) {
            for (int i = 0; i <= n-s; ++i) {
                int j = i + s;
                ll min_val = LLONG_MAX;
                for (int k = i + 1; k < j; ++k) {
                    ll tmp = dp[i][k] + dp[k][j] + dims[i] * dims[k] * dims[j];
                    if (tmp < min_val) {
                        min_val = tmp;
                        pre[i][j] = k;
                    }
                }
                dp[i][j] = min_val;
            }
        }
        num = 1;
        cout << "Case " << count << ": ";
        print_res(0, n);
        cout << endl;
    }

    return 0;
}
