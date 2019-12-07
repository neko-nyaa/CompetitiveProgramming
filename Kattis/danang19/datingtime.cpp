/*
	- There are 86400 seconds in a day. This is a small number.
	Let's iterate through every moments in which the two hands make an angle that is a multiple of 90.
	
	- Let's say the speed of the short hand is 1. Then the speed of the long hand is 12.
	Then the difference of their speed is 12 - 1 = 11.
	If the two hands make an angle of A, their distance is exactly 1/4.
	Initially at 00:00, the two hands make an angle of 0.
	After every 3/11 hours = 180/11 minutes, their distance change by exactly 1/4.

	- So we can iterate through every 3/11 hours, and check if it lies in the input range.
*/

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

int to_minute(string s) {
	int h = stoi(s.substr(0, 2));
	int m = stoi(s.substr(3, 2));

	return h*60 + m;
}

void solve() {
	string l, r; cin >> l >> r;
	int aleph; cin >> aleph;
	aleph /= 90;

	int L = to_minute(l);
	int R = to_minute(r);
	int ans = 0;
	for (int k = 0; k < 500; k++) {
		int tm = k*180;

		if (k % 4 == aleph || (aleph == 1 && k % 4 == 3)) {
			if (tm >= L*11 && tm <= R*11) ans++;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}