/*
	- Play it backwards
*/

#include <bits/stdc++.h>
using namespace std;

bool isClose(char c) {
	return c == ')' || c == '>' || c == '}' || c == ']';
}

bool match(char a, char b) {
	if (a == '(' && b == ')') return 1;
	if (a == '{' && b == '}') return 1;
	if (a == '[' && b == ']') return 1;
	if (a == '<' && b == '>') return 1;
	return 0;
}

void solve() {
	cout << '\n';

	string s; cin >> s;
	int n = s.size();
	vector<int> ans(n+1);

	stack<int> st;
	for (int i = n-1; i >= 0; i--) {
		if (isClose(s[i])) {
			st.push(i);
		} else {
			if (!st.empty()) {
				int prev = st.top(); st.pop();
				if (match(s[i], s[prev])) {
					ans[i] = ans[prev+1] + abs(prev - i + 1);
				} else {
					while (st.size()) st.pop();
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ":";
		solve();
	}
	
	return 0;
}