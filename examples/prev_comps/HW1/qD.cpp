#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef unsigned long long ull;


int main() {
    int T,N;
    ull s, a,b, cost;
    cin >> T;
    while (T--) {
        cin >> N;
        priority_queue<ull, vector<ull>, greater<ull>> min_heap;
        for (int i = 0; i < N; i++) { cin >> s; min_heap.push(s); }

        cost = 0;
        while (min_heap.size() > 1) {   // huffman
            a = min_heap.top(); min_heap.pop();
            b = min_heap.top(); min_heap.pop();
            cost += (a+b);
            min_heap.push(a+b);
        } if (min_heap.size() == 1) min_heap.pop();

        cout << cost << endl;
    }

    return 0;
}
