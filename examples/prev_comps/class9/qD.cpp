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
#include <unordered_map>
#include <numeric>
#include <iomanip>

#define loop(x,n) for(int x=0; x < n; ++x)
#define times(x) loop(__##x,x)
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<pdd> vdd;
typedef vector<vector<int>> graph;
typedef vector<vector<pii>> wgraph;
struct hash_pair {template <class T1, class T2> size_t operator()(const pair<T1, T2>& p) const
    {auto hash1 = hash<T1>{}(p.first); auto hash2 = hash<T2>{}(p.second); return hash1 ^ hash2;}};
#define EPS 1e-9

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
typedef vector<point> vp;
struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return {b.x - a.x, b.y - a.y}; }
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
double dist(point p1, point p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double
vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
    return {v.x * s, v.y * s}; }               // shorter.same.longer
point translate(point p, vec v) {        // translate p according to v
    return {p.x + v.x , p.y + v.y}; }
struct line { double a, b, c; };          // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - p1.y;
    } }
bool areParallel(line l1, line l2) {       // check coefficients a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;            // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true; }
// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
double distToLine(point p, point a, point b) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    point c = translate(a, scale(ab, u));                  // translate a to c
    return dist(p, c); }           // Euclidean distance between p and c
bool closestPoint(line l, point p, point &ans) {
    line perpendicular;         // perpendicular to l and pass through p
    if (fabs(l.b) < EPS) {              // special case 1: vertical line
        ans.x = -(l.c);
        ans.y = p.y;
        return true;
    }
    if (fabs(l.a) < EPS) {            // special case 2: horizontal line
        ans.x = p.x;
        ans.y = -(l.c);
        return true;
    }
    return false;
}
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { c = point(a.x, a.y);                   // closer to a
        return dist(p, a); }         // Euclidean distance between p and a
    if (u > 1.0) { c = point(b.x, b.y);                   // closer to b
        return dist(p, b); }         // Euclidean distance between p and b
    return distToLine(p, a, b); }          // run distToLine as above

int main() {
    int t, nin, nout;
    double x,y;
    cin >> t;
    for (int k = 0; k < t; ++k) {
        vp in;
        vp out;
        cin >> nin;
        times(nin) {
            cin >> x >> y;
            in.push_back({x, y});
        }
        in.push_back(in[0]);
        cin >> nout;
        times(nout) {
            cin >> x >> y;
            out.push_back({x, y});
        }
        out.push_back(out[0]);
        double best_yet = INFINITY;
        for (int i = 0; i < nout; ++i) {
            for (int j = 0; j < nin; ++j) {
                point p = in[j];
                point c;
                best_yet = min(distToLineSegment(p,out[i],out[i+1],c),best_yet);
            }
        }
        for (int i = 0; i < nin; ++i) {
            for (int j = 0; j < nout; ++j) {
                point p = out[j];
                point c;
                best_yet = min(distToLineSegment(p,in[i],in[i+1],c),best_yet);
            }
        }

        cout << fixed << setprecision(17) << best_yet/2 << endl;
    }
    return 0;
}

// Done by alon on the class
