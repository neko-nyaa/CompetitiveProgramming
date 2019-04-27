/*
	- Suppose we have any two points A and B in the rectilinear polygon.
	Then, point A attracts point B (and vice-versa) iff it's possible to go from one point to another without making a U-turn.
	- The points are given in counterclockwise order.
	So if we travel along the edges of the polygon in that order, then the inside of the polygon is always on the left of our direction.
	- Therefore, if we know the direction of two parallel edges and their relative position, we can determine if they make a U-turn.
	- Tterate over all consecutive pairs of parallel edges, and erase U-turns.
	- Finally just check if the remaining non-U-turn region is non-empty.
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000001;

typedef pair<int, int> point;
#define X first
#define Y second
int minx, miny, maxx, maxy;

int sign_func(int a, int b) {
	if (a - b > 0) return 1;
	else return -1;
}

void updateX(point a1, point a2, point b1, point b2) {
	// a1 to a2
	int sign1 = sign_func(a1.Y, a2.Y);
	int sign2 = sign_func(b1.Y, b2.Y);
	
	if (sign1 == sign2) return;
	// if sign > 0 --> move up 
	
	if (sign1 > sign2) {
		if (a1.X > b1.X) {
			miny = max(miny, a2.Y);
		}
	} else if (sign1 < sign2) {
		if (a1.X < b1.X) {
			maxy = min(maxy, a2.Y);
		}
	}
}

void updateY(point a1, point a2, point b1, point b2) {
	// a1 to a2
	int sign1 = sign_func(a1.X, a2.X);
	int sign2 = sign_func(b1.X, b2.X);
	
	if (sign1 == sign2) return;
	
	if (sign1 > sign2) { // right left
		if (a1.Y < b1.Y) {
			maxx = min(maxx, a2.X);
		}
	} else if (sign1 < sign2) {
		if (a1.Y > b1.Y) {
			minx = max(minx, a2.X);
		}
	}
}

void solve() {
	int n; cin >> n;
	vector<point> a(n);
	
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	
	minx = -INF, miny = -INF, maxx = INF, maxy = INF;
	
	// every down must be on the left of up
	// every left must be on the top of right
	// otherwise, there is a u-turn
	
	if (a[0].X != a[1].X) {
		a.push_back(a[0]);
		a.erase(a.begin());
	}
	// now a[0] and a[1] of the same x-coor
	
	for (int i = 0; i < 3; i++) {
		a.push_back(a[i]);
	}
	for (int i = 0; i < n; i += 2) {
		updateX(a[i], a[i+1], a[i+2], a[i+3]);
	}
	for (int i = 1; i < n; i += 2) {
		updateY(a[i], a[i+1], a[i+2], a[i+3]);
	}
	
	if (minx <= maxx && miny <= maxy) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	while (t--) {
		solve();
	}
	 
	return 0;
}