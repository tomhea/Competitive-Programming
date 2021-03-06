//
//  main.cpp
//  convexhull
//
//  Created by Yufei Zheng on 09/05/2018.
//  Copyright © 2018 Yufei Zheng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <math.h>

#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

struct PT
{
    double x,y;
    
    // compare the lexicographic order of 2 points
    // first compare x, if 2 x's are equal, compare y
    bool operator < (const PT& _p) const
    {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }
};

// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(PT& p1, PT& p2, PT& p3)
{
    double cross = (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);
    
    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}

int main() {
    
    vector<PT> Points;
    PT p;
    
    //-------- read point set from file -------
    ifstream myfile ("points.txt");
    if (myfile.is_open())
    {
        // cout << "open" << endl;
        while (myfile >> p.x >> p.y)
        {
            Points.push_back(p);
        }
        myfile.close();
    }
    else
        cout << "can't open file!" << endl;
    
    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<PT> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            PT p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (!left(Points[i], p2, p3)){
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (int i=0; i<Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<PT> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            PT p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (!left(Points[i], p2, p3)){
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }
    
    // print convex hull - cw order from leftmost point
    vector<PT> CH;
    stk_low.pop();
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    for (vector<PT>::const_iterator iter = CH.begin(); iter != CH.end(); iter++)
        cout << (*iter).x << ' ' << (*iter).y << endl;

    return 0;
}
