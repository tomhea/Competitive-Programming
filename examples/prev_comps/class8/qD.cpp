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
typedef vector<short> vi;
typedef pair<int, int> pii;

short possibleArr[30001];
vi bestBag[30001];

bool equalBags(vi new_bag,vi prevBag,int size){
    if(new_bag.size() != prevBag.size())
        return false;
    int foods1[101];
    int foods2[101];
    for (int i = 0; i < size; ++i) {
        foods1[i] = 0;
        foods2[i] = 0;
    }
    for (int j = 0; j < new_bag.size(); ++j) {
        foods1[new_bag.at(j)]++;
    }
    for (int j = 0; j < prevBag.size(); ++j) {
        foods2[prevBag.at(j)]++;
    }
    for (int i = 0; i < size; ++i) {
        if(foods1[i] != foods2[i])
            return false;
    }
    return true;
}

int f(vi& costs,int s){
    if(possibleArr[s] == 1){
        return 1;
    } else if(possibleArr[s] == -1){
        return -1;
    }
    int count = 0;
    vi prevBag;
    for (int i = 0; i < costs.size(); ++i) {
        if(s-costs.at(i)>=0){
            int possible = possibleArr[s-costs.at(i)];
            if(possible == 0)
                possible = f(costs,s-costs.at(i));
            if(possible == 1){
                if(count == 0) {
                    prevBag = bestBag[s - costs.at(i)];
                    count++;
                    vi bag(prevBag);
                    bag.push_back(i);
                    bestBag[s] = bag;
                    possibleArr[s] = 1;
                } else {
                    vi new_bag = bestBag[s - costs.at(i)];
                    vi try_bag(new_bag);
                    try_bag.push_back(i);
                    if(!equalBags(try_bag,bestBag[s],costs.size()))
                        count++;
                }
            }
            if(possible == -1 || count >= 2){
                possibleArr[s] = -1;
                return -1;
            }
        }
    }
    if(possibleArr[s] == 0)
        possibleArr[s] = -2;
    return possibleArr[s];
}

int main() {
    int n;
    cin >> n;
    vi costs;
    possibleArr[0] = 1;
    for (int k = 1; k < 30001; ++k) {
        possibleArr[k] = 0;
    }
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        costs.push_back(c);
    }
    vi empty;
    bestBag[0] = empty;

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int s;
        cin >> s;
        vi bag;
        int possible = possibleArr[s];
        if(possible == 0)
            possible = f(costs,s);
        if(possible == 1){
            vi bag = bestBag[s];
            sort(bag.begin(),bag.end());
            for (int j = 0; j < bag.size(); ++j) {
                cout << (bag.at(j)+1);

                if(j != bag.size()-1)
                    cout << " ";
            }
        } else if(possible == -2){
            cout << "Impossible";
        } else if(possible == -1){
            cout << "Ambiguous";
        }
        printf("\n");
    }
}