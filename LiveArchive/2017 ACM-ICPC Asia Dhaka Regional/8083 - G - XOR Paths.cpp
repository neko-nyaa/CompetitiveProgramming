/*
	- Root the tree anywhere. Find distance of path from root to every other roots.
	- Now for every i from 0 to 2^16 - 1 we want to count how many pair of paths from root that gives xor sum of i.
	- This is the definition of xor convolution. We can use Fast Walsh-Hadamard Transform for this.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> FWHT(vector<int> P, int n, bool inverse) {
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += 2 * len) {
			if (!inverse) {
				for (int j = 0; j < len; j++) {
					int u = P[i + j];
					int v = P[i + len + j];
					P[i + j] = u + v;
					P[i + len + j] = u - v;
				}
			} else {
				for (int j = 0; j < len; j++) {
					int u = P[i + j];
					int v = P[i + len + j];
					P[i + j] = (u + v)/2;
					P[i + len + j] = (u - v)/2;
				}
			}
		}
	}
	return P;
}

vector<int> xor_convolution(vector<int> a, vector<int> b, int deg) {
	a = FWHT(a, deg, 0);
	b = FWHT(b, deg, 0);

	vector<int> c;
	for (int i = 0; i < deg; i++) {
		c.push_back(a[i]*b[i]);
	}
	return FWHT(c, deg, 1);
}

int n;
vector<pair<int, int>> adj[100001];
vector<int> poly(100001);

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		adj[i].clear();
	}
	for (int i = 1; i < n; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].emplace_back(y, w);
		adj[y].emplace_back(x, w);
	}
	for (int i = 0; i <= (1 << 16); i++) {
		poly[i] = 0;
	}
}

void dfs(int now, int prev, int cnt) {
	poly[cnt]++;

	for (auto u: adj[now]) {
		if (u.first != prev) {
			dfs(u.first, now, cnt ^ u.second);
		}
	}
}

void solve() {
	dfs(1, 0, 0);
	vector<int> ans = xor_convolution(poly, poly, 1 << 16);

	ans[0] -= n;
	for (int i = 0; i < (1 << 16); i++) {
		cout << ans[i]/2 << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ":\n";
		input();
		solve();
	}
	
	return 0;
}