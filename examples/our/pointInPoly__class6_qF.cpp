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


bool pointInPoly2(vector<point> poly, int x, int y) {
    bool below;
    bool touch = false;
    bool on = false;
    int count = 0;
    int added = 0;
    int n = poly.size();

    int x1,y1, x2,y2;
    for (int i = 0; i < n+added; i++) {
        x1 = poly[i%n    ].x; y1 = poly[i%n    ].y;
        x2 = poly[(i+1)%n].x; y2 = poly[(i+1)%n].y;

        if ((y1 > y) && (y2 > y)) { below = false; touch = true; continue; }
        if ((y1 < y) && (y2 < y)) { below = true ; touch = true; continue; }

        if (y1 == y2) {
            if (y != y1) continue;
            if (((x1 <= x) && (x <= x2)) || ((x2 <= x) && (x <= x1))) {on = true; break;}
            continue;
        }
        double x_int;
        if (x2 == x1) x_int = x1;
        else {
            double a = double(y2 - y1) / double(x2 - x1);
            double b = y1 - a * x1;
            x_int = (y - b) / a;
        }

        if (abs(x_int - x) < EPS) {on = true; break;}

        if (x_int < x) { below = y1 < y; touch = true; continue; }

        if (y == y2) {
            below = y1 < y;
            touch = true;
            continue;
        }

        if (y == y1) {
            if (!touch) {
                added++;
                continue;
            }
            if (below != (y2 < y)) count++;
            continue;
        }

        if ((y1 <= y) && (y <= y2)) {
            count++;
            below = true;
            touch = true;
            continue;
        }

        if ((y2 <= y) && (y <= y1)) {
            count++;
            below = false;
            touch = true;
            continue;
        }

        below = y1 < y;
        touch = true;
    }
    if (on || count%2 == 1)
        return true;
    else {
        return false;
    }
}

bool pointInPoly(vector<point> poly, int x, int y) {
    point p(x,y);
    point origin = poly.at(0);

    double theta = atan2(y-origin.y,x-origin.x);
    int l=1, h = poly.size()-1;
    if(poly.at(h) == origin)
        h-=1;
    while(l<h){
        int mid = (h+l)/2;
        point t1 = poly.at(mid);
        point t2 = poly.at(mid+1);
        double thetaHigh = atan2(t1.y-origin.y,t1.x-origin.x);
        double thetaLow = atan2(t2.y-origin.y,t2.x-origin.x);
        if(thetaHigh < theta)
            h = mid;
        else if(thetaLow > theta)
            l = mid+1;
        else {
            vector<point> wedge;
            wedge.push_back(origin);
            wedge.push_back(t1);
            wedge.push_back(t2);
            wedge.push_back(origin);

            return pointInPoly2(wedge,x,y);
        }
    }
    return false;
}
