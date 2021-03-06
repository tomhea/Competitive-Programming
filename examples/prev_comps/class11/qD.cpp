// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

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
typedef set<unsigned long> si;
typedef vector<si> vsi;


map<unsigned long long, int> counts;

int solve(unsigned long long floor_number){
    if(counts.find(floor_number) != counts.end()){
        return counts.find(floor_number).operator*().second;
    }

    bitset<24> floor(floor_number);
    int min_count = floor.count();
    for (int i = 0; i < 23; ++i) {
        if (i<21){
            if(floor.test(i) && floor.test(i+1) && !floor.test(i+2)){
                bitset<24> copy(floor);
                copy.flip(i);
                copy.flip(i+1);
                copy.flip(i+2);
                unsigned long long copy_floor = copy.to_ulong();
                int count = solve(copy_floor);
                min_count = min(min_count,count);
            }
        }
        if (i>=2){
            if(floor.test(i) && floor.test(i-1) && !floor.test(i-2)){
                bitset<24> copy(floor);
                copy.flip(i);
                copy.flip(i-1);
                copy.flip(i-2);
                unsigned long long copy_floor = copy.to_ulong();
                int count = solve(copy_floor);
                min_count = min(min_count,count);
            }
        }
    }

    counts.insert(pair<unsigned long long, int>(floor_number,min_count));
    return min_count;

}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        bitset<24> floor;
        char x;
        for (int j = 0; j < 23; ++j) {
            cin >> x;
            if(x == 'o')
                floor.set(j,true);
            else{
                floor.set(j, true);
                floor.flip(j);
            }
        }

        unsigned long long floor_number = floor.to_ulong();
        counts.empty();
        int ans = solve(floor_number);
        printf("%d\n",ans);

    }


}