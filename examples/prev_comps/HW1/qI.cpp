#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef pair<double, double> pdd;
typedef pair<pdd, int> moment;
typedef pair<char,int> opcode;

#define EPS 1e-6


moment move(moment curr, opcode op) {
    double x = curr.first.first, y = curr.first.second;
    int angle = curr.second;
    char action = op.first;
    if (action == 'l' || action == 'r') {
        int angleChange = op.second;
        if (action == 'r') angleChange = -angleChange;
        angle = (angle + angleChange) % 360;
    } else {
        double dist = op.second;
        if (action == 'b') dist = -dist;
        x += dist*cos(angle*M_PI/180);
        y += dist*sin(angle*M_PI/180);
    }
    return {{x,y}, angle};
}

int main() {
    int tests, opNum, n;
    string actionString, nString;
    char action;
    cin >> tests;
    while (tests--) {
        vector<opcode> opsBefore, opsAfter;
        char missingOp = '\0';
        cin >> opNum;
        while (opNum--) {               // fetch input
            cin >> actionString >> nString;
            action = actionString[0];
            if (nString[0] == '?') {
                missingOp = action;
            } else {
                n = stoi(nString);
                if (missingOp == '\0') opsBefore.push_back({action, n});
                else opsAfter.push_back({action, n});
            }
        }
        if (missingOp == 'l' || missingOp == 'r') {
            for (int angle = 0; angle < 360; angle++) {     // brute-force over all 360 angles
                moment curr = {{0,0}, 0};

                for (opcode op : opsBefore) curr = move(curr, op);
                curr = move(curr, {missingOp, angle});
                for (opcode op : opsAfter ) curr = move(curr, op);

                double x = curr.first.first, y = curr.first.second;
                if ((fabs(x) < EPS) && (fabs(y) < EPS)) {
                    cout << angle << endl;
                    break;
                }
            }
        } else {                                            // execute known moves, and measure the distance from (0,0)
            moment curr = {{0,0}, 0};
            for (opcode op : opsBefore) curr = move(curr, op);
            for (opcode op : opsAfter ) curr = move(curr, op);

            double x = curr.first.first, y = curr.first.second;
            printf("%.0f\n", sqrt(x*x+y*y));
        }
    }

    return 0;
}
