/*
	- If we fix x, then it's a simple DP on DAG
	  Do a topological sort, then DP in the order we sorted

	- Ternary search on x

	- Since x is integer, binary search also possible
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, lo, hi;
vector<int> adj[10001];
vector<int> topo;
vector<int> b(10001), k(10001);
vector<int> deg(10001);

void toposort() {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) q.push(i); 
	}

	while (q.size()) {
		int k = q.front(); q.pop();
		topo.push_back(k);

		for (int u: adj[k]) {
			if (--deg[u] == 0) {
				q.push(u);
			}
		}
	}
}

void input() {
	cin >> n >> m;
	lo = -1000000, hi = 1000000;
	for (int i = 1; i <= n; i++) {
		adj[i].clear();
		cin >> b[i] >> k[i];

		if (k[i] > 0) {
			lo = max(lo, (1 - b[i])/k[i]);
			hi = min(hi, (50000 - b[i])/k[i]);
		} else if (k[i] < 0) {
			lo = max(lo, (50000 - b[i])/k[i]);
			hi = min(hi, (1 - b[i])/k[i]);
		}
	}
	topo.clear();
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		deg[y]++;
	}
	toposort();
}

int f(int x) {
	vector<int> dp(n+1);
	for (int i = 1; i <= n; i++) {
		dp[i] = b[i] + k[i]*x;
	}
	for (int i: topo) {
		for (int j: adj[i]) {
			dp[j] = max(dp[j], dp[i] + b[j] + k[j]*x);
		}
	}
	return *max_element(dp.begin(), dp.end());
}	

void solve() {
	while (lo + 3 < hi) {
		int m1 = lo + (hi - lo)/3;
		int m2 = hi - (hi - lo)/3;

		int f1 = f(m1);
		int f2 = f(m2);

		if (f1 < f2) {
			hi = m2;
		} else {
			lo = m1;
		}
	}
	
	int ans = 1000000000;
	for (int i = lo; i <= hi; i++) {
		ans = min(ans, f(i));
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		input(); solve();
	}
	
	return 0;
}