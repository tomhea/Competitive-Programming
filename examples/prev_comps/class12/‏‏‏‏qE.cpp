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
typedef pair<int,int> ii;
typedef pair<ll,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

bool isPrime(ll n){
    if(n<2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if(n%i == 0){
            return false;
        }
    }
    return true;
}


int comp(int number){
    int sum = 0;
    int temp = number;
    while(temp != 0){
        sum += (temp%10)*(temp%10);
        temp/=10;
    }
    return sum;
}

int main() {
    int N;
    map<int,int> mapping;
    mapping.insert(pair<int,int>(1,1));

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int k,m;
        cin >> k >> m;
        int keep = m;
        if(m == 1 || !isPrime(keep)){
            printf("%d %d NO\n",k,keep);
            continue;
        }
        vector<int> path;
        while(mapping.find(m) == mapping.end()){
            mapping.insert(pair<int,int>(m,0));
            path.push_back(m);
            m = comp(m);
        }
        if(mapping[m] == 1){
            for (int j = 0; j < path.size(); ++j) {
                mapping[path[j]] = 1;
            }
        }
        if(mapping[m] == 0 || mapping[m] == 2){
            for (int j = 0; j < path.size(); ++j) {
                mapping[path[j]] = 2;
            }
        }
        if(mapping[keep] == 1)
            printf("%d %d YES\n",k,keep);
        else
            printf("%d %d NO\n",k,keep);

    }


    return 0;
}
