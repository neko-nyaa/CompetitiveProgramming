#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m; cin >> n >> m;
	int x = 0, y = 0;
	for (int i = 0; i < m; i++) {
		int k; cin >> k;
		x *= 10; x += k;
	}
	for (int i = 0; i < m; i++) {
		int k; cin >> k;
		y *= 10; y += k;
	}

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a.push_back(a[i]);
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		int t = 0;
		for (int j = 0; j < m; j++) {
			t *= 10; t += a[i+j];
		}
		ans += (t <= y && t >= x);
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) solve();

	return 0;
}