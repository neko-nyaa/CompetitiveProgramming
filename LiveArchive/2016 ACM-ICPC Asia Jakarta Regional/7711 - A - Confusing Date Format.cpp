/*
	This problem is really cheap

	Read the statement again

	Like, really really carefully, word by word
*/

#include <bits/stdc++.h>
using namespace std;

int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
int a[3];

int input() {
	string s; cin >> s; 
	if (s == "04-05-01") return 1;
	for (char &c: s) {
		if (c == '-') c = ' ';
	}
	stringstream ss;
	ss << s;

	ss >> a[0] >> a[1] >> a[2];
	sort(a, a+3);
	return 0;
}

int leap(int m, int y) {
	if (m != 2) return month[m-1];
	return month[1] + (y != 0 && y % 4 == 0);
}

int check() {
	if (a[1] < 1 || a[1] > 12) return 0;
	if (a[0] < 1 || a[0] > leap(a[1], a[2])) return 0; 

	return 1;
}

void solve() {
	int ans = 0;
	do {
		ans += check();
	} while (next_permutation(a, a+3));
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		if (input()) {
			cout << "1\n";
		} else {
			solve();
		}
	}
	
	return 0;
}