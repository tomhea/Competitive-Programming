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
typedef vector< vector<int> > vvi;

int main() {
    int N;
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int v,e, f;
        cin >> v >> e >> f;
        vvi graph;
        for (int j = 0; j < v; ++j) {
            vi v_g;
            graph.push_back(v_g);
        }
        for (int k = 0; k < e; ++k) {
            int a,b;
            cin >> a >> b;
            graph.at(a-1).push_back(b-1);
        }

        int size = v;
        bool* fallen = new bool[size];
        for(int i=0;i<size;i++)
            fallen[i] = false;
        int count = 0;

        for(int i=0;i<f;i++){
            int f_in;
            cin >> f_in;
            stack<int> stack1;
            stack1.push(f_in-1);
            while(!stack1.empty()){
                int x = stack1.top();
                stack1.pop();
                if(fallen[x]) {
                    continue;
                }
                fallen[x] = true;
                count++;
                for(int neight: graph[x]){
                    stack1.push(neight);
                }
            }

        }

        printf("%d\n",count);
    }

}