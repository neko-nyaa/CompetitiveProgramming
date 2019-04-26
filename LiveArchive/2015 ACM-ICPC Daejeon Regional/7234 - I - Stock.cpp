#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<long long> a(n);
	for (long long &i: a) cin >> i;
	
	long long ans = 0, mx = 0;
	for (int i = n-1; i >= 0; i--) {
		mx = max(mx, a[i]);
		ans += mx - a[i];
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) solve();

	return 0;
}