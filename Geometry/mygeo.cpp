#include<bits/stdc++.h>
using namespace std;
#define mx 1000005
#define ll long long
#define md 1000000007

typedef long double T;
const T PI = acos(-1), EPS = 1e-9;
int dcmp(T x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);}

struct pt {
	T x, y;
	pt(T x = 0, T y = 0) : x(x), y(y) {}

	void read () { scanf("%lf%lf", &x, &y); }
	void write () { printf("%lf %lf\n", x, y); }

	pt operator + (const pt& u) const { return pt(x + u.x, y + u.y); }
	pt operator - (const pt& u) const { return pt(x - u.x, y - u.y); }
	pt operator * (const long long u) const { return pt(x * u, y * u); }
	pt operator*(T d) {return {x * d, y * d};}
	pt operator/(T d) {return {x / d, y / d};} // only for floatingpoint

	bool operator == (const pt& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
	bool operator != (const pt& u) const { return !(*this == u); }
	bool operator < (const pt& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }

	friend ostream& operator<<(ostream& os, pt p) {
		return os << "(" << p.x << "," << p.y << ")"; /// Some example usage: pt a{3, 4}, b{2, -1};
	}
	friend istream &operator >> (istream &is, pt &p) { return is >> p.x >> p.y; }
};
/// It returns -1 for negative numbers, 0 for zero, and 1 for positive numbers.
template <typename T> int sgn(T x) {
	return (T(0) < x) - (x < T(0));
}

T radian(T a) {return a * PI / 180.0;}
T degree(T a) {return a * 180.0 / PI;}

T sq(pt p) {return p.x * p.x + p.y * p.y;}
double abs(pt p) {return sqrt(sq(p));} /// length

/*To translate an object by a vector #»v , we simply need to add #»v to every point in the object of vector p*/
pt translate(pt v, pt p) {return p + v;}

/*To scale an object by a certain ratio α around a center c, we need to shorten
or lengthen the vector from c to every point by a factor α, while conserving
the direction.*/
pt scale(pt c, double factor, pt p) {
	return c + (p - c) * factor;
}

/*Rotation   In particular, we will often use the (counter-clockwise) rotation centered
on the origin. where theta = a*/
pt rot(pt p, double a) {
	return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

/* 90 Degree rotation */
pt perp(pt p) {return { -p.y, p.x};}

T dot(pt v, pt w) {return v.x * w.x + v.y * w.y;}
T cross(pt v, pt w) {return v.x * w.y - v.y * w.x;}

/*f(r) = f(p) + ((r − p) ∗ f(q) − f(p) / (q − p))*/
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
	pt pq = q - p, num{cross(pq, fq - fp), dot(pq, fq - fp)};
	pt fr;
	return fr = fp + pt{cross(r - p, num), dot(r - p, num)} / sq(pq);
}

/// return true if two vectors v and w are perpendicular
bool isPerp(pt v, pt w) {return dot(v, w) == 0;}

/// angle between vector v and vector w
double angle(pt v, pt w) {
	double cosTheta = dot(v, w) / abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, cosTheta)));
}
double angle(pt v, pt w, bool bk) {
	return atan2(cross(v, w), dot(v, w));
}

/// return 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(pt a, pt b, pt c) {return dcmp(cross(b - a, c - a));} /// OK

/// return 1 if point p is in angle CAB
bool inAngle(pt a, pt b, pt c, pt p) {
	assert(orient(a, b, c) != 0);
	if (orient(a, b, c) < 0) swap(b, c);
	return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

/// angle between Orient AB and point C
double orientedAngle(pt a, pt b, pt c) {
	if (orient(a, b, c) >= 0)
		return angle(b - a, c - a);
	else
		return 2 * M_PI - angle(b - a, c - a);
}

/// return 1 if given point is convex polygon
bool isConvex(vector<pt> p) {
	bool hasPos = false, hasNeg = false;
	for (int i = 0, n = p.size(); i < n; i++) {
		int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
		if (o > 0) hasPos = true;
		if (o < 0) hasNeg = true;
	}
	return !(hasPos && hasNeg);
}

/// return 1 if point p
// bool inDisk(pt a, pt b, pt p) {
//     return dcmp(dot(a - p, b - p)) <= 0;
// }

// bool onSegment(pt a, pt b, pt p) {
//     return dcmp(orient(a, b, p)) == 0 && inDisk(a, b, p);
// }

// /// return 1 if two lines are intersected;
// bool LineLineIntersection(pt a, pt b, pt c, pt d) /// OK /*https://cses.fi/problemset/task/2190*/
// {
//     return (orient(a, b, c) != orient(a, b, d) && orient(c, d, a) != orient(c, d, b)) ||
//            onSegment(a, b, c) || onSegment(a, b, d) ||
//            onSegment(c, d, a) || onSegment(c, d, b);
// }

struct line {
	pt v; T c;
// From direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {}
// From equation ax+by=c
	line(T a, T b, T c) : v( {b, -a}), c(c) {}
// From points P and Q
	line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
// Will be defined later:
// - these work with T = int

	/// return 1 for p is ccw side, 0 for p is in line, -1 for p is in cw
	T side(pt p) {return cross(v, p) - c;}

	/// distance from point p to line l
	T dist(pt p) {return abs(side(p)) / abs(v);}

	/// squared distance from point p to lone l
	T sqDist(pt p) {return side(p) * side(p) / (double)sq(v);}

	/// To find a line perpendicular to line l and which goes through a certain point P
	line perpThrough(pt p) {return {p, p + perp(v)};}

	/*given points on a line l, to sort them in the order they appear on the line,
	following the direction of #»v .*/

	/*In fact, this comparator is more powerful than we need: it is not limited to
	points on l and can compare two points by their orthogonal projection3 on l.*/
	bool cmpProj(pt p, pt q) {
		return dot(v, p) < dot(v, q);
	}

	/*If we want to translate a line l by vector #»t , the direction vector #»v remains
	the same but we have to adapt c.*/
	line translate(pt t) {return {v, c + cross(v, t)};}

	/*A closely related task is shifting line l to the left by a certain distance δ
	(or to the right by −δ).*/
	line shiftLeft(double dist) {return {v, c + dist * abs(v)};}

	/*The orthogonal projection of a point P on a line l is the point on l that is
	closest to P. The reflection of point P by line l is the point on the other side
	of l that is at the same distance and has the same orthogonal projection*/
	pt proj(pt p) {return p - perp(v) * side(p) / sq(v);}

	/*To find the reflection, we need to move P in the same direction but twice
	the distance:*/
	pt refl(pt p) {return p - perp(v) * 2 * side(p) / sq(v);}
};

/// distance between two parallal line l1, l2
T Dist(line l2, line l1) {return (l2.c - l1.c) / abs(l1.v);}

/// There is a unique intersection point between two lines l1 and l2 if and only if # »vl1 != »vl2
bool inter(line l1, line l2, pt &out) {
	T d = cross(l1.v, l2.v);
	if (d == 0) return false;
	out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
	return true;
}

/*An important property of bisectors is that their points are at equal distances from the original lines l1 and l2. In fact, if we give a sign to the
	distance depending on which side of the line we are on, we can say that
	lint(l1, l2) is the line whose points are at opposite distances from l1 and l2
	while lext(l1, l2) is the line whose points are at equal distances from l1 and
	l2.*/
/// angle bisector line, if iteratior is 1 then return internal line otherwise external line...
line bisector(line l1, line l2, bool interior) {
	assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
	double sign = interior ? 1 : -1;
	return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
	        l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}

/*For this we will first define a useful subroutine inDisk() that checks if
a point P lies on the disk of diameter [AB]. */
bool inDisk(pt a, pt b, pt p) {
	return dot(a - p, b - p) <= 0;
}

int main()
{
	pt a{3, 7}, b{13, 7}, c{8, 2}, d{9, 8}, xx;

	ll ans = 0;
	cout << a << " " << b << " " << c << endl; /// 1
	cout << abs(a) << endl; /// 2 Length

	cout << sgn(b.y) << endl; /// 3 Sign of b.y

	cout << translate(b, a) << endl; /// 4 Transation of vector a for every point of b

	cout << scale(c, 2, a) << endl; /// 5 Salling
	T alpha = radian(90);

	cout << rot(a, alpha) << endl; /// 6 Rotation vector v of angle alpha radian

	cout << perp(a) << endl; /// 7 Rotation 90* of vector a

	cout << linearTransfo(a, b, c, a, b) << endl; /// 8 Find last point of linearTransfo

	cout << isPerp(a, b) << endl; /// 9 Is vector a is perpendicular to vector b

	cout << angle(a, b) << endl; /// 10 angle between vector v and vector w

	cout << angle(a, b, 1) << endl; /// 11 sign angle between vector v and vector w

	cout << orient(a, b, c) << endl; /// 12 returns 1 if c is left of ab, 0 if on ab && -1 if right of ab

	cout << inAngle(xx, a, b, c) << endl; /// 13 return 1 if point p is in angle CAB

	cout << degree(orientedAngle(a, b, c)) << endl; /// 14 angle between Orient AB and point C

	cout << isConvex({a, b, c}) << endl; /// 15 return 1 if given point is convex polygon

	line l1 = line(a, b);

	pt e{18, 2};

	cout << l1.side({13, 7}) << endl; /// 16

	cout << l1.dist(e) << endl; /// 17

	cout << l1.sqDist(e) << endl; /// 18

	line l2 = l1.perpThrough(c);


	cout << l2.side(e) << endl; /// 19

	line paral2 = l2.translate(e - c); /// (e - c) because of line l2 is in c point, so c works at axix, so line in point(18, 0) to (18, inf)

	cout << paral2.side({18, 6}) << endl; /// 20

	line distt = paral2.shiftLeft(10);
	cout << l2.v << " " << distt.v << endl; /// 21 after shifting horil2 in left in 10 unit

	cout << Dist(paral2, l2) << endl; /// 22 line line distance

	pt intersention_point;

	cout << inter(l1, l2, intersention_point) << endl; /// 23 is line l1 and l2 intersected?
	cout << intersention_point << endl; /// 24 intersection point of line l1 and l2

	cout << l1.proj(c) << endl; /// 25 projection point from point c to line l1

	cout << l1.refl(c) << endl; /// 26 reflection point of point p with line l1

	cout << bisector(l1, l2, 1).v << endl; /// 27 internal or external Line of line l1 and l2

	return 0;
}