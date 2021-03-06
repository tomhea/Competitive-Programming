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
typedef vector<ull> vu;
typedef vector<double> vd;

typedef pair<int, int> pii;
typedef pair<pii, pii> ppp;
typedef pair<ull, ull> puu;
typedef pair<double, double> pdd;

typedef vector<pii> vii;
typedef vector<puu> vuu;
typedef vector<pdd> vdd;

typedef vector<vi> vvi;
typedef vector<vu> vvu;
typedef vector<vd> vvd;

typedef vector<vii> vvii;
typedef vector<vuu> vvuu;
typedef vector<vdd> vvdd;


pii intersect(ppp a, ppp b) {
    double ax1 = a.first.first,ay1 = a.first.second, ax2 = a.second.first, ay2 = a.second.second;
    double bx1 = b.first.first,by1 = b.first.second, bx2 = b.second.first, by2 = b.second.second;
}

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

// struct point_i { int x, y; };    // basic raw form, minimalist mode
struct point_i { int x, y;     // whenever possible, work with point_i
    point_i() { x = y = 0; }                      // default constructor
    point_i(int _x, int _y) : x(_x), y(_y) {} };         // user-defined

struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator < (point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y; }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };

struct line { double a, b, c; };          // a way to represent a line

bool areParallel(line l1, line l2) {       // check coefficients a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) {           // also check coefficient c
    return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;            // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true; }

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - p1.y;
    } }

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

	int n;
	double x1,y1, x2,y2;
	while (cin >> n) {
	    if (n == 0) break;
	    vector<pair<point, point>> lines(n);
	    for (int i = 0; i < n; i++) {
	        cin >> x1 >> y1 >> x2 >> y2;
	        point a(x1,y1), b(x2,y2);
	        lines[i] = {a,b};
	    }
	    point p;
	    ull tris = 0;
	    line l1,l2,l3;
	    point s1,s2,s3,e1,e2,e3;
	    for (int i1 = 0; i1 < n; i1++) {
	        s1 = lines[i1].first; e1 = lines[i1].second;
	        pointsToLine(s1, e1, l1);
            for (int i2 = i1+1; i2 < n; i2++) {
                s2 = lines[i2].first; e2 = lines[i2].second;
                pointsToLine(s2,e2, l2);
                if (!areIntersect(l1, l2, p)) continue;
                if (max(s1.x,e1.x) < p.x || min(s1.x,e1.x) > p.x) continue;
                if (max(s2.x,e2.x) < p.x || min(s2.x,e2.x) > p.x) continue;
                for (int i3 = i2+1; i3 < n; i3++) {
                    s3 = lines[i3].first; e3 = lines[i3].second;
                    pointsToLine(s3,e3, l3);
                    if (!areIntersect(l3, l1, p)) continue;
                    if (max(s1.x,e1.x) < p.x || min(s1.x,e1.x) > p.x) continue;
                    if (max(s3.x,e3.x) < p.x || min(s3.x,e3.x) > p.x) continue;
                    if (!areIntersect(l3, l2, p)) continue;
                    if (max(s2.x,e2.x) < p.x || min(s2.x,e2.x) > p.x) continue;
                    if (max(s3.x,e3.x) < p.x || min(s3.x,e3.x) > p.x) continue;
                    tris++;
                }
            }
	    }
	    cout << tris << endl;

	}

    return 0;
}
