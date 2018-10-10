/*
      https://community.topcoder.com/stat?c=problem_statement&pm=15098&rd=17298&rm=331762&cr=40629265

      - Given set of points, check if they form vertices of a simple polygon in that order. The definition of a simple polygon is in statements.

      - This problem is actually tricky, there are a lot of conditions to be checked. Carefully examining the statements helps a lot.

      - We will need to check for the following conditions:
            + All side lengths are positive.
            + No three consecutive points are collinear.
            + All pairs of none-consecutive sides do not intersect.
      If all these conditions are met, we will find the area. This can be done with shoelace formula.

      - The constrains are extremely important here. All points have integer coordinates, so we can avoid working with floating-point numbers entirely.
      Area will be either integer or half-integer. Use long long for every calculations.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
#define X first
#define Y second

class CheckPolygon{
public:
	string no = "Not simple";

	ll dist(point a, point b) {
		return (a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y);
	}

	int onSegment(point p, point q, point r) {
		// return 1 if q between p and r
		ll k = dist(p, r);

		return (k == dist(p, q) + dist(q, r));
	}

	int orientation(point p, point q, point r) {
		ll det = (q.Y - p.Y) * (r.X - q.X) - (q.X - p.X) * (r.Y - q.Y);

		if (det == 0) return 0;

		if (det > 0) return 1;		// clock
		else return -1;			// counter clock
	}

	int intersect(point p1, point q1, point p2, point q2) {
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4) return 1;
		if (o1 == 0 && onSegment(p1, p2, q1)) return 1;
		if (o2 == 0 && onSegment(p1, q2, q1)) return 1;
		if (o3 == 0 && onSegment(p2, p1, q2)) return 1;
		if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

		return 0;
	}

	string check(vector<int> x, vector<int> y) {
		int n = x.size();
		vector<point> p;
		for (int i = 0; i < n; i++) {
			p.push_back(make_pair(x[i], y[i]));
		}
		p.push_back(p[0]);
		p.push_back(p[1]);

		for (int i = 1; i <= n; i++) {
			if (orientation(p[i-1], p[i], p[i+1]) == 0 || dist(p[i-1], p[i]) == 0 || dist(p[i], p[i+1]) == 0) {return no;}
		}

		vector<pair<point, point>> line;
		for (int i = 1; i <= n; i++) {
			line.push_back(make_pair(p[i], p[i-1]));
		}

		n = line.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (abs(i-j) <= 1) continue;
				if (i == 0 && j == n-1) continue;
				if (j == 0 && i == n-1) continue;

				if (intersect(line[i].first, line[i].second, line[j].first, line[j].second)) return no;
			}
		}

		p.pop_back();
		p.pop_back();

		n = p.size();
		int prev = n-1;
		ll area = 0;

		for (int i = 0; i < n; i++) {
			area += (p[prev].X + p[i].X)*(p[prev].Y - p[i].Y);
			prev = i;
		}

		ll ans = abs(area);

		string s;

		if (ans % 2) {
			s += to_string(ans/2) + ".5";
		} else {
			s += to_string(ans/2) + ".0";
		}

		return s;
	}
};
