#include <bits/stdc++.h>
using namespace std;

void solve() {
	long long e, p, k, r; cin >> e >> p >> k >> r;

	if (p*k >= e) {
		cout << (e + p - 1)/p << '\n';
	} else if (p*k <= r) {
		cout << "-1\n";
	} else {
		int profit = p*k - r;
		int reload_times = (e - p*k + profit - 1)/profit;
		e -= profit*reload_times;

		cout << reload_times*k + (e + p - 1)/p << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ": ";
		solve();
	}
	
	return 0;
}