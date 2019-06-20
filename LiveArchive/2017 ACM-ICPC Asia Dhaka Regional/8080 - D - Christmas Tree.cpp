#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a[1001];

void input() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		a[i].clear();
	}
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
}

int dfs(int now, int prev) {
	vector<int> child;
	for (int u: a[now]) {
		if (u != prev) {
			child.push_back(dfs(u, now));
		}
	}

	int ans = 1;
	if (child.size() >= k) {
		sort(child.begin(), child.end(), greater<int>());
		for (int i = 0; i < k; i++) {
			ans += child[i];
		}
	}
	return ans;
}

void solve() {
	cout << dfs(1, 0) << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case " << i << ": ";
		input(); solve();
	}
	
	return 0;
}