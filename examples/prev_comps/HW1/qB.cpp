#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

#define BELOW_ZERO 100000

const int N = 2*BELOW_ZERO+1;  // limit for array size
int n = N;  // array size
int t[2 * N];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r) {  // max on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) if (t[l++] > res) res = t[l-1];
        if (r&1) if (t[--r] > res) res = t[r];
    }
    return res;
}


int main() {
    int nn,q,a,s,e;
    vi arr;
    while (cin >> nn) {
        if (nn == 0) break;
        for (int i = 0; i < n; ++i)
            t[n+i]=0;//init array
        build();

        cin >> q;
        vi start(BELOW_ZERO*2-1, -1), end(BELOW_ZERO*2-1, -1);
        start.assign(nn, -1); end.assign(nn, -1);
        arr.clear();
        for (int i = 0; i < nn; i++) {
            cin >> a; a += BELOW_ZERO;
            arr.push_back(a);
            modify(a, 1 + t[n+a]);

            if(start[a] == -1) start[a] = i;
            end[a] = i;
        }
        while (q--) {
            cin >> s >> e; s--; e--;
            int as=arr[s], ae=arr[e];

            modify(as, query(as, as+1)-(s-start[as])); modify (ae, query(ae, ae+1)-(end[ae]-e));
            int maxC = query(as, ae+1);
            modify(as, end[as]-start[as]+1); modify(ae, end[ae]-start[ae]+1);
            cout << maxC << endl;
        }
    }
    return 0;
}
