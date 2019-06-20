/*
	For each object, find its see-range
	Then prefix sum
*/

#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
	vector<int> pref(10508);

	while (n--) {
		int x, y; cin >> x >> y;
		int l = max(0, x-y);
		int r = x+y;

		pref[l]++; pref[r+1]--;
	}

	int ans = 0;
	for (int i = 1; i <= 10500; i++) {
		pref[i] += pref[i-1];
		ans = max(ans, pref[i]);
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	while (cin >> n, n) {
		solve(n);
	}
	
	return 0;
}