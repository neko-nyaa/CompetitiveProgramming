/*
	- The process of building the shortest path tree is similar to building convex hull.
	- Consider the histogram contains all the query points.
	- While doing monotone chain, add edge from point u to the previous point of the lower convex hull ending at u.
	- Then we get a tree, distance to query is simply distance in the tree.
	- I do dijkstra because it can be copy pasted, and I'm a little lazy.
*/

#include <bits/stdc++.h>
using namespace std;

struct point{
	long long x, y;
	int ind;

	bool operator <(const point &b) {
		if (b.ind == 0) return 0;
		return ind == 0 || ind > b.ind;
	}

	bool operator ==(const point &b) {
		return (x == b.x && y == b.y);
	}
};

int n, m;
vector<pair<int, double>> adj[200003];
vector<int> isque(200003);
vector<point> a;

void input() {
	a.clear();

	cin >> n;
	for (int i = 0; i < n; i++) {
		long long x, y; cin >> x >> y;
		a.push_back({x, y, i});
	}
	cin >> m;
	vector<pair<int, int>> qr;
	for (int i = 0; i < m; i++) {
		long long id, d; cin >> id >> d;
		qr.emplace_back(id, d);
	}
	sort(qr.begin(), qr.end());
	reverse(qr.begin(), qr.end());
	
	for (int i = 0; i < m+n; i++) {
		adj[i].clear(); isque[i] = 0;
	}
	a.push_back(a[0]);

	vector<point> f;
	for (int i = 0, k = 0; i < n; i++) {
		f.push_back({a[i].x, a[i].y, k++});

		int dx, dy;
		if (a[i].x == a[i+1].x) {
			dx = 0; 
			if (a[i].y < a[i+1].y) dy = 1;
			else dy = -1;
		} else {
			dy = 0; 
			if (a[i].x < a[i+1].x) dx = 1;
			else dx = -1;	
		}

		while (qr.size() && qr.back().first == i) {
			f.push_back({a[i].x + dx*qr.back().second, a[i].y + dy*qr.back().second, k});
			qr.pop_back();
			isque[k++] = 1;
		}
	}

	swap(a, f);
}

int check(point a, point b, point c) {
	long long val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

	if (val == 0) return 0;       // collinear
	return (val > 0) ? -1: 1;     // counter-clockwise and clockwise
}

double dist(point a, point b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double INF = 1e18;

vector<double> dijkstra(int start) {
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	vector<double> dist(n+m, INF);
	vector<int> vis(n+m);
	dist[start] = 0;

	pq.push({0LL, start});
	while (pq.size()) {
		auto tmp = pq.top();
		int now = tmp.second;
		pq.pop();

		if (vis[now]) continue;
		vis[now] = 1;

		for (auto u: adj[now]) {
			if (dist[now] + u.second < dist[u.first]) {
				dist[u.first] = dist[now] + u.second;
				pq.push({dist[u.first], u.first});
			}
		}
	}

	return dist;
}

void solve() {
	sort(a.begin(), a.end());
	
	vector<point> hull;
	int k = 0;
	for (auto p: a) {
		int x = p.x, y = p.y, i = p.ind;

		while (k >= 2 && check(hull[k-2], hull[k-1], p) <= 0) {
			k--;
			hull.pop_back();
		}

		if (k != 0) {
			adj[i].emplace_back(hull.back().ind, dist(p, hull.back()));
			adj[hull.back().ind].emplace_back(i, dist(p, hull.back()));
		}

		hull.push_back(p); k++;
	}

	vector<double> d = dijkstra(0);
	double ans = 0;
	for (int i = 0; i < n+m; i++) {
		if (isque[i]) {ans += d[i];}
	}

	cout << fixed << setprecision(1) << ans << '\n'; 
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		input();
		solve();
	}

	return 0;
}