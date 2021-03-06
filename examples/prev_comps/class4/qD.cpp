#include <deque>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

// Most of the code was written through class4 competition, and minor bugs fixed later. Team c+++.

#define BIGNUM 1000000000000000000
#define BIGBIGNUM 10000000000000000000

ull calcTimes(int si, int mi, int di, vector<vi> ingr, vi brands) {

    set<int> currIngr;
    for (int ing : ingr[si]) currIngr.insert(ing);
    for (int ing : ingr[mi]) currIngr.insert(ing);
    for (int ing : ingr[di]) currIngr.insert(ing);

    ull poss = 1, a,b;
    for (int ing : currIngr) {
        a = poss; b = brands[ing];
        poss = a * b;
        if (a != 0 && poss / a != b) return BIGBIGNUM;   // overflaw..
    }
    return poss;
}

int main() {
    ull poss = 0;

    int r,s,m,d,n;
    cin >> r >> s >> m >> d >> n;
    vi brands(r);
    for (int i = 0; i < r; i++) cin >> brands[i];
    int k;
    vector<vector<int>> ingr(s+m+d);
    for (int i = 0; i < s+m+d; i++) {
        cin >> k;
        vi tempV(k);
        for (int j = 0; j < k; j++) {cin >> tempV[j]; tempV[j]--;}
        ingr[i] = tempV;
    }
    set<pii> bad;
    int t1,t2;
    for (int i = 0; i < n; i++) {
        cin >> t1 >> t2;
        bad.insert(pii(t1-1, t2-1));
        bad.insert(pii(t2-1, t1-1));
    }

    for (int si = 0; si < s; si++) {
        for (int mi = s; mi < s+m; mi++) {
            if (bad.find(pii(si, mi)) != bad.end()) continue;
            for (int di = s+m; di < s+m+d; di++) {
                if (bad.find(pii(di, si)) != bad.end()) continue;
                if (bad.find(pii(di, mi)) != bad.end()) continue;

                ull possMore = calcTimes(si, mi, di, ingr, brands);
                if (possMore > BIGNUM || poss + possMore > BIGNUM) goto tooMany;
                poss += possMore;
            }
        }

    }


    cout << poss << endl;
    return 0;

    tooMany:
    cout << "too many" << endl;
    return 0;
}
