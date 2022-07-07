/**
C++ routines for Computational Geometry (2D)
Courtesy:  nodim, imAnik, rebornplusplus, solaimanope, anachor
*/

#include <bits/stdc++.h>
using namespace std;

typedef double Tf;
typedef Tf Ti;      /// use long long for exactness
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);}

struct Point {
    Ti x, y;
    Point(Ti x = 0, Ti y = 0) : x(x), y(y) {}

    void read () { scanf("%lf%lf", &x, &y); }
    void write () { printf("%lf %lf\n", x, y); }

    Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
    Point operator * (const long long u) const { return Point(x * u, y * u); }
    Point operator * (Tf u) { return Point(x * u, y * u); }
    Point operator / (const Tf u) const { return Point(x / u, y / u); }

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const Point& u) const { return !(*this == u); }
    bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }
    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};

Ti dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
Ti cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
Tf length(Point a) { return sqrt(dot(a, a)); }
Ti sqLength(Point a) { return dot(a, a); }
Tf distance(Point a, Point b) {return length(a - b);}
Tf angle(Point u) { return atan2(u.y, u.x); }

// returns angle between oa, ob in (-PI, PI]
Tf angleBetween(Point a, Point b) {
    double ans = angle(b) - angle(a);
    return ans <= -PI ? ans + 2 * PI : (ans > PI ? ans - 2 * PI : ans);
}

// Rotate a ccw by rad radians
Point rotate(Point a, Tf rad) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

// rotate a ccw by angle th with cos(th) = co && sin(th) = si
Point rotatePrecise(Point a, Tf co, Tf si) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * co - a.y * si, a.y * co + a.x * si);
}

Point rotate90(Point a) { return Point(-a.y, a.x); }

// scales vector a by s such that length of a becomes s
Point scale(Point a, Tf s) {
    static_assert(is_same<Tf, Ti>::value);
    return a / length(a) * s;
}

// returns an unit vector perpendicular to vector a
Point normal(Point a) {
    static_assert(is_same<Tf, Ti>::value);
    Tf l = length(a);
    return Point(-a.y / l, a.x / l);
}

// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c) {
    return dcmp(cross(b - a, c - a));
}

bool half(Point p) {     // returns true for point above x axis or on negative x axis
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

bool polarComp(Point p, Point q) { //to be used in sort() function
    return make_tuple(half(p), 0) < make_tuple(half(q), cross(p, q));
}

/* To scale an object by a certain ratio α around a center c, we need to shorten
or lengthen the vector from c to every point by a factor α, while conserving the direction */
Point scale(Point c, double factor, Point p) {
    return c + (p - c) * factor;
}

/// return trye if vector v is perpendicular with vector w
bool isPerpendicular(Point v, Point w) {return dot(v, w) == 0;}

/// perpendicular length from vector w to v

Tf PerpenduculLength(Point v, Point w) { Tf ret = cross(v, w) / length(v); return dcmp(ret) < 0 ? -ret : ret;}

/// return true if point p is in the angle (cab)     assertion check?
bool inAngle(Point a, Point b, Point c, Point p) {
    if (orient(a, b, c) == 0) return false;
    assert(orient(a, b, c) != 0);

    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

// not proved
Tf orientedAngle(Point a, Point b, Point c) {
    if (orient(a, b, c) >= 0)
        return angleBetween(b - a, c - a);
    else
        return 2 * PI - angleBetween(b - a, c - a);
}

struct Segment {
    Point a, b;
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;

struct line {
    Point tem1, tem2;
    Point v; Tf c;
// From direction vector v and offset c
    line(Point v, Tf c) : v(v), c(c) {}
// From equation ax+by=c
    line(Tf a, Tf b, Tf c) : v( {b, -a}), c(c) {}
// From points P and Q
    line(Point p, Point q) : v(q - p), tem1(p), tem2(q), c(cross(v, p)) {}
// Will be defined later:
// - these work with Tf = int

    /// return 1 for p is ccw side, 0 for p is in line, -1 for p is in cw
    Tf side(Point p) {return cross(v, p) - c;}

    /// distance from point p to line l
    Tf dist(Point p) {return length(side(p)) / length(v);}

    /// squared distance from point p to lone l
    Tf sqDist(Point p) {return side(p) * side(p) / (double)sqLength(v);}

    /// To find a line perpendicular to line l and which goes through a certain point P
    line perPointhrough(Point p) {return {p, p + rotate90(v)};}

    /*given points on a line l, to sort them in the order they appear on the line,
    following the direction of #»v .*/

    /*In fact, this comparator is more powerful than we need: it is not limited to
    points on l and can compare two points by their orthogonal projection3 on l.*/
    bool cmpProj(Point p, Point q) {
        return dot(v, p) < dot(v, q);
    }

    /*If we want to translate a line l by vector #»t , the direction vector #»v remains
    the same but we have to adaPoint c.*/
    line translate(Point t) {return {v, c + cross(v, t)};}

    /*A closely related task is shifting line l to the left by a certain distance δ
    (or to the right by −δ).*/
    line shiftLeft(double dist) {return {v, c + dist * length(v)};}

    /*The orthogonal projection of a point P on a line l is the point on l that is
    closest to P. The reflection of point P by line l is the point on the other side
    of l that is at the same distance and has the same orthogonal projection*/
    Point proj(Point p) {return p - rotate90(v) * side(p) / sqLength(v);}

    /*To find the reflection, we need to move P in the same direction but twice
    the distance:*/
    Point refl(Point p) {return p - (rotate90(v) * 2) * side(p) / sqLength(v);}
};

struct Circle {
    Point o;
    Tf r;
    Circle(Point o = Point(0, 0), Tf r = 0) : o(o), r(r) {}

    // returns true if point p is in || on the circle
    bool contains(Point p) {
        return dcmp(sqLength(p - o) - r * r) <= 0;
    }

    // returns a point on the circle rad radians away from +X CCW
    Point point(Tf rad) {
        static_assert(is_same<Tf, Ti>::value);
        return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }

    // area of a circular sector with central angle rad
    Tf area(Tf rad = PI + PI) { return rad * r * r / 2; }

    // area of the circular sector cut by a chord with central angle alpha
    Tf sector(Tf alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};

namespace Linear {
// returns true if point p is on segment s
bool onSegment(Point p, Segment s) {
    return dcmp(cross(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
}

// returns true if segment p && q touch or intersect
bool segmentsIntersect(Segment p, Segment q) {
    if (onSegment(p.a, q) || onSegment(p.b, q)) return true;
    if (onSegment(q.a, p) || onSegment(q.b, p)) return true;

    Ti c1 = cross(p.b - p.a, q.a - p.a);
    Ti c2 = cross(p.b - p.a, q.b - p.a);
    Ti c3 = cross(q.b - q.a, p.a - q.a);
    Ti c4 = cross(q.b - q.a, p.b - q.a);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool linesParallel(Line p, Line q) {
    return dcmp(cross(p.b - p.a, q.b - q.a)) == 0;
}

// lines are represented as a ray from a point: (point, vector)
// returns false if two lines (p, v) && (q, w) are parallel or collinear
// true otherwise, intersection point is stored at o via reference
bool lineLineIntersection(Point p, Point v, Point q, Point w, Point& o) {
    static_assert(is_same<Tf, Ti>::value);
    if (dcmp(cross(v, w)) == 0) return false;
    Point u = p - q;
    o = p + v * (cross(w, u) / cross(v, w));
    return true;
}

// returns false if two lines p && q are parallel or collinear
// true otherwise, intersection point is stored at o via reference
bool lineLineIntersection(Line p, Line q, Point& o) {
    return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
}

/*
There are many possible ways to define a line in 2D and you shouldn't hesitate to combine them.
 For example we have two lines and we want to find their intersection points.
  We can say that all points from first line can be parameterized as  where  is initial point,
    is direction and  is some real parameter. As for second line all its points must satisfy .
     From this we can easily find parameter :
*/
Point lineLineIntersectionPoint(Point a1, Point d1, Point a2, Point d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) / length(d1);
}

// returns the distance from point a to line l
Tf distancePointLine(Point p, Line l) {
    return abs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
}

// returns the shortest distance from point a to segment s
Tf distancePointSegment(Point p, Segment s) {
    if (s.a == s.b) return length(p - s.a);
    Point v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
    if (dcmp(dot(v1, v2)) < 0)     return length(v2);
    else if (dcmp(dot(v1, v3)) > 0)  return length(v3);
    else return length(cross(v1, v2) / length(v1));
}

// returns the shortest distance from segment p to segment q
Tf distanceSegmentSegment(Segment p, Segment q) {
    if (segmentsIntersect(p, q)) return 0;
    Tf ans = distancePointSegment(p.a, q);
    ans = min(ans, distancePointSegment(p.b, q));
    ans = min(ans, distancePointSegment(q.a, p));
    ans = min(ans, distancePointSegment(q.b, p));
    return ans;
}

// returns the projection of point p on line l
Point projectPointLine(Point p, Line l) {
    static_assert(is_same<Tf, Ti>::value);
    Point v = l.b - l.a;
    return l.a + v * ((Tf) dot(v, p - l.a) / dot(v, v));
}
}  // namespace Linear
using namespace Linear;

typedef vector<Point> Polygon;
namespace Polygonal {
// returns the signed area of polygon p of n vertices
Tf signedPolygonArea(Polygon p) {
    Tf ret = 0;
    for (int i = 0; i < (int) p.size() - 1; i++)
        ret += cross(p[i] - p[0],  p[i + 1] - p[0]);
    return ret / 2;
}

// given a polygon p of n vertices, generates the convex hull in ch
// in CCW && returns the number of vertices in the convex hull
int convexHull(Polygon p, Polygon &ch) {
    sort(p.begin(), p.end());
    int n = p.size();
    ch.resize(n + n);
    int m = 0;    // preparing lower hull
    for (int i = 0; i < n; i++) {
        while (m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;    // preparing upper hull
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0) m--;
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    ch.resize(m);
    return m;
}

/// return true if polygon p is a Convex polygon
/// not proved
bool isConvex(vector<Point> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

// for a point o and polygon p returns:
//   -1 if o is strictly inside p
//  0 if o is on a segment of p
//  1 if o is strictly outside p
// computes via winding numbers
int pointInPolygon(Point o, Polygon p) {
    using Linear::onSegment;
    int wn = 0, n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (onSegment(o, Segment(p[i], p[j])) || o == p[i]) return 0;
        int k = dcmp(cross(p[j] - p[i], o - p[i]));
        int d1 = dcmp(p[i].y - o.y);
        int d2 = dcmp(p[j].y - o.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn ? -1 : 1;
}


// returns the longest line segment of l that is inside or on the
// simply polygon p. O(n lg n). TESTED: TIMUS 1955
Tf longestSegInPoly(Line l, const Polygon &p) {
    using Linear::lineLineIntersection;
    int n = p.size();
    vector<pair<Tf, int>> ev;
    for (int i = 0; i < n; ++i) {
        Point a = p[i], b = p[(i + 1) % n], z = p[(i - 1 + n) % n];
        int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b), orz = orient(l.a, l.b, z);
        if (!ora) {
            Tf d = dot(a - l.a, l.b - l.a);
            if (orz && orb) {
                if (orz != orb) ev.emplace_back(d, 0);
            }
            else if (orz) ev.emplace_back(d, orz);
            else if (orb) ev.emplace_back(d, orb);
        }
        else if (ora == -orb) {
            Point ins;
            lineLineIntersection(l, Line(a, b), ins);
            ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
        }
    }
    sort(ev.begin(), ev.end());

    Tf ret = 0, cur = 0, pre = 0;
    bool active = false;
    int sign = 0;
    for (auto &qq : ev) {
        int tp = qq.second;
        Tf d = qq.first;
        if (sign) {
            cur += d - pre;
            ret = max(ret, cur);
            if (tp != sign) active = !active;
            sign = 0;
        }
        else {
            if (active) cur += d - pre, ret = max(ret, cur);
            if (tp == 0) active = !active;
            else sign = tp;
        }
        pre = d;
        if (!active) cur = 0;
    }

    ret /= length(l.b - l.a);
    return ret;
}
}  // namespace Polygonal
using namespace Polygonal;

namespace Convex {
///Tested on Kattis::fenceortho
void rotatingCalipersGetRectangle(Point* p, int n, Tf& area, Tf& perimeter) {
    using Linear::distancePointLine;
    static_assert(is_same<Tf, Ti>::value);
    p[n] = p[0];
    int l = 1, r = 1, j = 1;
    area = perimeter = 1e100;

    for (int i = 0; i < n; i++) {
        Point v = (p[i + 1] - p[i]) / length(p[i + 1] - p[i]);
        while (dcmp(dot(v, p[r % n] - p[i]) - dot(v, p[(r + 1) % n] - p[i])) < 0) r++;
        while (j < r || dcmp(cross(v, p[j % n] - p[i]) - cross(v, p[(j + 1) % n] - p[i])) < 0) j++;
        while (l < j || dcmp(dot(v, p[l % n] - p[i]) - dot(v, p[(l + 1) % n] - p[i])) > 0) l++;
        Tf w = dot(v, p[r % n] - p[i]) - dot(v, p[l % n] - p[i]);
        Tf h = distancePointLine(p[j % n], Line(p[i], p[i + 1]));
        area = min(area, w * h);
        perimeter = min(perimeter, 2 * w + 2 * h);
    }
}

// returns the left side of polygon u after cutting it by ray a->b
Polygon cutPolygon(Polygon u, Point a, Point b) {
    using Linear::lineLineIntersection, Linear::onSegment;

    Polygon ret;
    int n = u.size();
    for (int i = 0; i < n; i++) {
        Point c = u[i], d = u[(i + 1) % n];
        if (dcmp(cross(b - a, c - a)) >= 0) ret.push_back(c);
        if (dcmp(cross(b - a, d - c)) != 0) {
            Point t;
            lineLineIntersection(a, b - a, c, d - c, t);
            if (onSegment(t, Segment(c, d))) ret.push_back(t);
        }
    }
    return ret;
}

// returns true if point p is in or on triangle abc
bool pointInTriangle(Point a, Point b, Point c, Point p) {
    return dcmp(cross(b - a, p - a)) >= 0
           && dcmp(cross(c - b, p - b)) >= 0
           && dcmp(cross(a - c, p - c)) >= 0;
}

// Tested : https://www.spoj.com/problems/INOROUT
// pt must be in ccw order with no three collinear points
// returns inside = -1, on = 0, outside = 1
int pointInConvexPolygon(const Polygon &pt, Point p) {
    int n = pt.size();
    assert(n >= 3);

    int lo = 1, hi = n - 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (dcmp(cross(pt[mid] - pt[0], p - pt[0])) > 0) lo = mid;
        else  hi = mid;
    }

    bool in = pointInTriangle(pt[0], pt[lo], pt[hi], p);
    if (!in) return 1;

    if (dcmp(cross(pt[lo] - pt[lo - 1], p - pt[lo - 1])) == 0) return 0;
    if (dcmp(cross(pt[hi] - pt[lo], p - pt[lo])) == 0) return 0;
    if (dcmp(cross(pt[hi] - pt[(hi + 1) % n], p - pt[(hi + 1) % n])) == 0) return 0;
    return -1;
}

// Extreme Point for a direction is the farthest point in that direction
// O'Rourke, page 270, http://crtl-i.com/PDF/comp_c.pdf
// also https://codeforces.com/blog/entry/48868
// poly is a convex polygon, sorted in CCW, doesn't contain redundant points
// u is the direction for extremeness
int extremePoint(const Polygon &poly, Point u = Point(0, 1)) {
    int n = (int) poly.size();
    int a = 0, b = n;
    while (b - a > 1) {
        int c = (a + b) / 2;
        if (dcmp(dot(poly[c] - poly[(c + 1) % n], u)) >= 0 && dcmp(dot(poly[c] - poly[(c - 1 + n) % n], u)) >= 0) {
            return c;
        }

        bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
        bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
        bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;

        if (a_up && !c_up) b = c;
        else if (!a_up && c_up) a = c;
        else if (a_up && c_up) {
            if (a_above_c) b = c;
            else a = c;
        }
        else {
            if (!a_above_c) b = c;
            else a = c;
        }
    }

    if (dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 && dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
        return a;
    return b % n;
}

// For a convex polygon p and a line l, returns a list of segments
// of p that are touch or intersect line l.
// the i'th segment is considered (p[i], p[(i + 1) modulo |p|])
// #1 If a segment is collinear with the line, only that is returned
// #2 Else if l goes through i'th point, the i'th segment is added
// If there are 2 or more such collinear segments for #1,
// any of them (only one, not all) should be returned (not tested)
// Complexity: O(lg |p|)
vector<int> lineConvexPolyIntersection(const Polygon &p, Line l) {
    assert((int) p.size() >= 3);
    assert(l.a != l.b);

    int n = p.size();
    vector<int> ret;

    Point v = l.b - l.a;
    int lf = extremePoint(p, rotate90(v));
    int rt = extremePoint(p, rotate90(v) * Ti(-1));
    int olf = orient(l.a, l.b, p[lf]);
    int ort = orient(l.a, l.b, p[rt]);

    if (!olf || !ort) {
        int idx = (!olf ? lf : rt);
        if (orient(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
            ret.push_back((idx - 1 + n) % n);
        else  ret.push_back(idx);
        return ret;
    }
    if (olf == ort) return ret;

    for (int i = 0; i < 2; ++i) {
        int lo = i ? rt : lf;
        int hi = i ? lf : rt;
        int olo = i ? ort : olf;

        while (true) {
            int gap = (hi - lo + n) % n;
            if (gap < 2) break;

            int mid = (lo + gap / 2) % n;
            int omid = orient(l.a, l.b, p[mid]);
            if (!omid) {
                lo = mid;
                break;
            }
            if (omid == olo) lo = mid;
            else hi = mid;
        }
        ret.push_back(lo);
    }
    return ret;
}

// Tested : https://toph.co/p/cover-the-points
// Calculate [ACW, CW] tangent pair from an external point
constexpr int CW = -1, ACW = 1;
bool isGood(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) != -dir; }
Point better(Point u, Point v, Point Q, int dir) { return orient(Q, u, v) == dir ? u : v; }
Point pointPolyTangent(const Polygon &pt, Point Q, int dir, int lo, int hi) {
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
        bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);

        if (pvs && nxt) return pt[mid];
        if (!(pvs || nxt)) {
            Point p1 = pointPolyTangent(pt, Q, dir, mid + 1, hi);
            Point p2 = pointPolyTangent(pt, Q, dir, lo, mid - 1);
            return better(p1, p2, Q, dir);
        }

        if (!pvs) {
            if (orient(Q, pt[mid], pt[lo]) == dir)         hi = mid - 1;
            else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
            else  lo = mid + 1;
        }
        if (!nxt) {
            if (orient(Q, pt[mid], pt[lo]) == dir)         lo = mid + 1;
            else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])   hi = mid - 1;
            else  lo = mid + 1;
        }
    }

    Point ret = pt[lo];
    for (int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
    return ret;
}
// [ACW, CW] Tangent
pair<Point, Point> pointPolyTangents(const Polygon &pt, Point Q) {
    int n = pt.size();
    Point acw_tan = pointPolyTangent(pt, Q, ACW, 0, n - 1);
    Point cw_tan = pointPolyTangent(pt, Q, CW, 0, n - 1);
    return make_pair(acw_tan, cw_tan);
}
}

namespace Circular {
// Extremely inaccurate for finding near touches
// compute intersection of line l with circle c
// The intersections are given in order of the ray (l.a, l.b)
vector<Point> circleLineIntersection(Circle c, Line l) {
    static_assert(is_same<Tf, Ti>::value);
    vector<Point> ret;
    Point b = l.b - l.a, a = l.a - c.o;

    Tf A = dot(b, b), B = dot(a, b);
    Tf C = dot(a, a) - c.r * c.r, D = B * B - A * C;
    if (D < -EPS) return ret;

    ret.push_back(l.a + b * (-B - sqrt(D + EPS)) / A);
    if (D > EPS)
        ret.push_back(l.a + b * (-B + sqrt(D)) / A);
    return ret;
}

// signed area of intersection of circle(c.o, c.r) &&
// triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
Tf circleTriangleIntersectionArea(Circle c, Segment s) {
    using Linear::distancePointSegment;
    Tf OA = length(c.o - s.a);
    Tf OB = length(c.o - s.b);

    // sector
    if (dcmp(distancePointSegment(c.o, s) - c.r) >= 0)
        return angleBetween(s.a - c.o, s.b - c.o) * (c.r * c.r) / 2.0;

    // triangle
    if (dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
        return cross(c.o - s.b, s.a - s.b) / 2.0;

    // three part: (A, a) (a, b) (b, B)
    vector<Point> Sect = circleLineIntersection(c, s);
    return circleTriangleIntersectionArea(c, Segment(s.a, Sect[0]))
           + circleTriangleIntersectionArea(c, Segment(Sect[0], Sect[1]))
           + circleTriangleIntersectionArea(c, Segment(Sect[1], s.b));
}

// area of intersecion of circle(c.o, c.r) && simple polyson(p[])
// Tested : https://codeforces.com/gym/100204/problem/F - Little Mammoth
Tf circlePolyIntersectionArea(Circle c, Polygon p) {
    Tf res = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i)
        res += circleTriangleIntersectionArea(c, Segment(p[i], p[(i + 1) % n]));
    return abs(res);
}

// locates circle c2 relative to c1
// interior       (d < R - r)     ----> -2
// interior tangents (d = R - r)     ----> -1
// concentric    (d = 0)
// secants       (R - r < d < R + r) ---->  0
// exterior tangents (d = R + r)     ---->  1
// exterior       (d > R + r)     ---->  2
int circleCirclePosition(Circle c1, Circle c2) {
    Tf d = length(c1.o - c2.o);
    int in = dcmp(d - abs(c1.r - c2.r)), ex = dcmp(d - (c1.r + c2.r));
    return in < 0 ? -2 : in == 0 ? -1 : ex == 0 ? 1 : ex > 0 ? 2 : 0;
}

// compute the intersection points between two circles c1 && c2
vector<Point> circleCircleIntersection(Circle c1, Circle c2) {
    static_assert(is_same<Tf, Ti>::value);

    vector<Point> ret;
    Tf d = length(c1.o - c2.o);
    if (dcmp(d) == 0) return ret;
    if (dcmp(c1.r + c2.r - d) < 0) return ret;
    if (dcmp(abs(c1.r - c2.r) - d) > 0) return ret;

    Point v = c2.o - c1.o;
    Tf co = (c1.r * c1.r + sqLength(v) - c2.r * c2.r) / (2 * c1.r * length(v));
    Tf si = sqrt(abs(1.0 - co * co));
    Point p1 = scale(rotatePrecise(v, co, -si), c1.r) + c1.o;
    Point p2 = scale(rotatePrecise(v, co, si), c1.r) + c1.o;

    ret.push_back(p1);
    if (p1 != p2) ret.push_back(p2);
    return ret;
}

// intersection area between two circles c1, c2
Tf circleCircleIntersectionArea(Circle c1, Circle c2) {
    Point AB = c2.o - c1.o;
    Tf d = length(AB);
    if (d >= c1.r + c2.r) return 0;
    if (d + c1.r <= c2.r) return PI * c1.r * c1.r;
    if (d + c2.r <= c1.r) return PI * c2.r * c2.r;

    Tf alpha1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
    Tf alpha2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
    return c1.sector(2 * alpha1) + c2.sector(2 * alpha2);
}

// returns tangents from a point p to circle c
vector<Point> pointCircleTangents(Point p, Circle c) {
    static_assert(is_same<Tf, Ti>::value);

    vector<Point> ret;
    Point u = c.o - p;
    Tf d = length(u);
    if (d < c.r) ;
    else if (dcmp(d - c.r) == 0) {
        ret = { rotate(u, PI / 2) };
    }
    else {
        Tf ang = asin(c.r / d);
        ret = { rotate(u, -ang), rotate(u, ang) };
    }
    return ret;
}

// returns the points on tangents that touches the circle
vector<Point> pointCircleTangencyPoints(Point p, Circle c) {
    static_assert(is_same<Tf, Ti>::value);

    Point u = p - c.o;
    Tf d = length(u);
    if (d < c.r) return {};
    else if (dcmp(d - c.r) == 0)   return {c.o + u};
    else {
        Tf ang = acos(c.r / d);
        u = u / length(u) * c.r;
        return { c.o + rotate(u, -ang), c.o + rotate(u, ang) };
    }
}

// for two circles c1 && c2, returns two list of points a && b
// such that a[i] is on c1 && b[i] is c2 && for every i
// Line(a[i], b[i]) is a tangent to both circles
// CAUTION: a[i] = b[i] in case they touch | -1 for c1 = c2
int circleCircleTangencyPoints(Circle c1, Circle c2, vector<Point> &a, vector<Point> &b) {
    a.clear(), b.clear();
    int cnt = 0;
    if (dcmp(c1.r - c2.r) < 0) {
        swap(c1, c2); swap(a, b);
    }
    Tf d2 = sqLength(c1.o - c2.o);
    Tf rdif = c1.r - c2.r, rsum = c1.r + c2.r;
    if (dcmp(d2 - rdif * rdif) < 0) return 0;
    if (dcmp(d2) == 0 && dcmp(c1.r - c2.r) == 0) return -1;

    Tf base = angle(c2.o - c1.o);
    if (dcmp(d2 - rdif * rdif) == 0) {
        a.push_back(c1.point(base));
        b.push_back(c2.point(base));
        cnt++;
        return cnt;
    }

    Tf ang = acos((c1.r - c2.r) / sqrt(d2));
    a.push_back(c1.point(base + ang));
    b.push_back(c2.point(base + ang));
    cnt++;
    a.push_back(c1.point(base - ang));
    b.push_back(c2.point(base - ang));
    cnt++;

    if (dcmp(d2 - rsum * rsum) == 0) {
        a.push_back(c1.point(base));
        b.push_back(c2.point(PI + base));
        cnt++;
    }
    else if (dcmp(d2 - rsum * rsum) > 0) {
        Tf ang = acos((c1.r + c2.r) / sqrt(d2));
        a.push_back(c1.point(base + ang));
        b.push_back(c2.point(PI + base + ang));
        cnt++;
        a.push_back(c1.point(base - ang));
        b.push_back(c2.point(PI + base - ang));
        cnt++;
    }
    return cnt;
}
}  // namespace Circular

namespace EnclosingCircle {
// returns false if points are collinear, true otherwise
// circle p touch each arm of triangle abc
bool inscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::distancePointLine;
    static_assert(is_same<Tf, Ti>::value);
    if (orient(a, b, c) == 0) return false;
    Tf u = length(b - c);
    Tf v = length(c - a);
    Tf w = length(a - b);
    p.o = (a * u + b * v + c * w) / (u + v + w);
    p.r = distancePointLine(p.o, Line(a, b));
    return true;
}

// set of points A(x, y) such that PA : QA = rp : rq
Circle apolloniusCircle(Point P, Point Q, Tf rp, Tf rq) {
    static_assert(is_same<Tf, Ti>::value);
    rq *= rq; rp *= rp; Tf a = rq - rp; assert(dcmp(a));
    Tf g = (rq * P.x - rp * Q.x) / a, h = (rq * P.y - rp * Q.y) / a;
    Tf c =   (rq * P.x * P.x - rp * Q.x * Q.x
              + rq * P.y * P.y - rp * Q.y * Q.y) / a;
    Point o(g, h); Tf R = sqrt(g * g + h * h - c);
    return Circle(o, R);
}
// returns false if points are collinear
bool circumscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::lineLineIntersection;
    if (orient(a, b, c) == 0) return false;
    Point d = (a + b) / 2, e = (a + c) / 2;
    Point vd = rotate90(b - a), ve = rotate90(a - c);
    bool f = lineLineIntersection(d, vd, e, ve, p.o);
    if (f) p.r = length(a - p.o);
    return f;
}

// Following three methods implement Welzl's algorithm for
// the smallest enclosing circle problem: Given a set of
// points, find out the minimal circle that covers them all.
// boundary(p) determines (if possible) a circle that goes
// through the points in p. Ideally |p| <= 3.
// welzl() is a recursive helper function doing the most part
// of Welzl's algorithm. Call minidisk with the set of points
// Randomized Complexity: O(CN) with C~10 (practically lesser)
// TESTED: ICPC Dhaka 2019 - I (CodeMarshal)

Circle boundary(const vector<Point> &p) {
    Circle ret;
    int sz = p.size();
    if (sz == 0)       return Circle({0, 0}, 0);
    else if (sz == 1) ;
    else if (sz == 2)  ret.o = (p[0] + p[1]) / 2, ret.r = length(p[0] - p[1]) / 2;
    else if (!circumscribedCircle(p[0], p[1], p[2], ret))  ret.r = 0;
    return ret;
}
Circle welzl(const vector<Point> &p, int fr, vector<Point> &b) {
    if (fr >= (int) p.size() || b.size() == 3)   return boundary(b);

    Circle c = welzl(p, fr + 1, b);
    if (!c.contains(p[fr])) {
        b.push_back(p[fr]);
        c = welzl(p, fr + 1, b);
        b.pop_back();
    }
    return c;
}
Circle minidisk(vector<Point> p) {
    random_shuffle(p.begin(), p.end());
    vector<Point> q;
    return welzl(p, 0, q);
}
}


// Given a bunch of segments. Check if any two intersect.
// Sweep Line. O(n lg n). TESTED: CF 1359F
namespace IntersectingSegments {
Tf yvalSegment(const Line &s, Tf x) {
    if (dcmp(s.a.x - s.b.x) == 0) return s.a.y;
    return s.a.y + (s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
}

struct SegCompare {
    bool operator () (const Segment &p, const Segment &q) const {
        Tf x = max(min(p.a.x, p.b.x), min(q.a.x, q.b.x));
        return dcmp(yvalSegment(p, x) - yvalSegment(q, x)) < 0;
    }
};

multiset<Segment, SegCompare> st;
typedef multiset<Segment, SegCompare>::iterator iter;

iter prev(iter it) {
    return it == st.begin() ? st.end() : --it;
}

iter next(iter it) {
    return it == st.end() ? st.end() : ++it;
}

struct Event {
    Tf x;
    int tp, id;
    Event(Ti x, int tp, int id) : x(x), tp(tp), id(id) { }
    bool operator < (const Event &p) const {
        if (dcmp(x - p.x)) return x < p.x;
        return tp > p.tp;
    }
};

bool anyIntersection(const vector<Segment> &v) {
    using Linear::segmentsIntersect;
    vector<Event> ev;
    for (int i = 0; i < (int) v.size(); ++i) {
        ev.push_back(Event(min(v[i].a.x, v[i].b.x), +1, i));
        ev.push_back(Event(max(v[i].a.x, v[i].b.x), -1, i));
    }
    sort(ev.begin(), ev.end());

    st.clear();
    vector<iter> where(v.size());
    for (auto &cur : ev) {
        int id = cur.id;
        if (cur.tp == 1) {
            iter nxt = st.lower_bound(v[id]);
            iter pre = prev(nxt);
            if (pre != st.end() && segmentsIntersect(*pre, v[id]))   return true;
            if (nxt != st.end() && segmentsIntersect(*nxt, v[id]))   return true;
            where[id] = st.insert(nxt, v[id]);
        }
        else {
            iter nxt = next(where[id]);
            iter pre = prev(where[id]);
            if (pre != st.end() && nxt != st.end() && segmentsIntersect(*pre, *nxt))
                return true;
            st.erase(where[id]);
        }
    }
    return false;
}
}

namespace Voronoi {
using Linear::lineLineIntersection;
struct DirLine {
    Point p, v;
    Tf ang;
    DirLine() {}
    /// Directed line containing point P in the direction v
    DirLine(Point p, Point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator<(const DirLine& u) const { return ang < u.ang; }
};
// returns true if point p is on the ccw-left side of ray l
bool onLeft(DirLine l, Point p) { return dcmp(cross(l.v, p - l.p)) >= 0; }


// Given a set of directed lines returns a polygon such that
// the polygon is the intersection by halfplanes created by the
// left side of the directed lines. MAY CONTAIN DUPLICATE POINTS
int halfPlaneIntersection(vector<DirLine> &li, Polygon &poly) {
    int n = li.size();
    sort(li.begin(), li.end());

    int first, last;
    Point* p = new Point[n];
    DirLine* q = new DirLine[n];
    q[first = last = 0] = li[0];

    for (int i = 1; i < n; i++) {
        while (first < last && !onLeft(li[i], p[last - 1])) last--;
        while (first < last && !onLeft(li[i], p[first])) first++;
        q[++last] = li[i];

        if (dcmp(cross(q[last].v, q[last - 1].v)) == 0) {
            last--;
            if (onLeft(q[last], li[i].p)) q[last] = li[i];
        }

        if (first < last)
            lineLineIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
    }

    while (first < last && !onLeft(q[first], p[last - 1])) last--;
    if (last - first <= 1) {
        delete[] p;
        delete[] q;
        poly.clear();
        return 0;
    }
    lineLineIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);

    int m = 0;
    poly.resize(last - first + 1);
    for (int i = first; i <= last; i++) poly[m++] = p[i];
    delete[] p;
    delete[] q;
    return m;
}

// O(n^2 lg n) implimentation of Voronoi Diagram bounded by INF square
// DEF: The partition of plane with points into convex polygons s.t.
// each polygon contains exactly one generating point && every point
// in a given polygon is closer to it's generating point than others.
const double INF = 1e10;
void voronoi(const vector<Point> &site, vector<Polygon> &region, Tf bsq) {
    int n = site.size();
    region.resize(n);
    Point A(-bsq, -bsq), B(bsq, -bsq), C(bsq, bsq), D(-bsq, bsq);

    for (int i = 0; i < n; ++i) {
        vector<DirLine> li(n - 1);
        for (int j = 0, k = 0; j < n; ++j) {
            if (i == j) continue;
            li[k++] = DirLine((site[i] + site[j]) / 2, rotate90(site[j] - site[i]));
        }
        li.emplace_back(A, B - A);
        li.emplace_back(B, C - B);
        li.emplace_back(C, D - C);
        li.emplace_back(D, A - D);
        halfPlaneIntersection(li, region[i]);
    }
}
}
///Tests: https://docs.google.com/spreadsheets/d/1juON6i98qXcm9dC55LjB2Xi4W7rj0KMVnnMDO2hANJg/edit?ts=6027e43b#gid=1812406598

void solve()
{
    Point a{3, 7}, b{13, 7}, c{8, 2}, d{9, 8}, xx;

    line l1 = line(a, b);

    Point e{18, 2};

    cout << l1.side(e) << endl; /// 16

    cout << l1.dist(e) << endl; /// 17

    cout << l1.sqDist(e) << endl; /// 18

    line l2 = l1.perPointhrough(c);


    cout << l2.side(e) << endl; /// 19

    line paral2 = l2.translate(e - c); /// (e - c) because of line l2 is in c point, so c works at axix, so line in point(18, 0) to (18, inf)

    cout << paral2.side({18, 6}) << endl; /// 20

    line distt = paral2.shiftLeft(10);
    cout << l2.v << " " << distt.v << endl; /// 21 after shifting horil2 in left in 10 unit
}

int main()
{
    int t = 1, cs = 1;

    // cin >> t;
    for (int i = 1; i <= t; i++) {
        // cout << "Case " << i << ": ";
        solve();
    }
}
