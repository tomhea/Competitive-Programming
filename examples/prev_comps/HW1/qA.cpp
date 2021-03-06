#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


struct event {
    int time, jump;
    bool start;

    bool operator()(const event& e1, const event& e2) {
        if (e1.time > e2.time) return true ;
        if (e1.time < e2.time) return false;
        return !e1.start || e2.start;
    }
};


bool findConflicts(int n, int m) {
    int s,e,j;
    std::priority_queue<event, vector<event>, event> q;
    while (n--) {
        cin >> s >> e;
        q.push({s,0,true});
        q.push({e-1,0,false});
    }
    while (m--) {
        cin >> s >> e >> j;
        q.push({s,j,true});
        q.push({e-1,j,false});
    }
    bool started = false;
    while (!q.empty()) {
        event curr = q.top(); q.pop();
        if (curr.start && started) return true;
        started = curr.start;
        if (curr.jump>0 && (curr.time+curr.jump<1000000)) q.push({curr.time + curr.jump, curr.jump, curr.start});
    }
    return false;
}


int main() {
    int n,m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        cout << (findConflicts(n, m) ? "CONFLICT" : "NO CONFLICT") << endl;
    }
    return 0;
}
