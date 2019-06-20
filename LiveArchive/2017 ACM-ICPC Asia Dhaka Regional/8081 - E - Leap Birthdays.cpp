/*
	Usually this asks us to check whether a date is valid
	I'm so thankful this doesn't
*/

#include <bits/stdc++.h>
using namespace std;

bool isLeapYear(int year) {
	if (year % 400 == 0) return true;
	else if (year % 100 == 0) return false;
	else if (year % 4 == 0) return true;
	else return false;
}

void solve() {
	int d, m, y, qy, ans = 0;
	cin >> d >> m >> y >> qy;
	for (y++; y <= qy; y++) {
		if (d == 29 && m == 2) {
			ans += isLeapYear(y);
		} else {
			ans++;
		}
	}
	cout << ans << '\n';
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