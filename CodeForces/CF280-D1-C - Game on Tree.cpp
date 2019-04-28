/*
	https://codeforces.com/contest/280/problem/C

	- This problem is actually super simple.

	- The expected number of moves to delete the tree is simply the sum of probabilities that node X will be picked for all nodes X.

	- For a node to be possibly picked, the condition is that none of its ancestors were picked before.

	- So the probability of a node gets picked is 1/ancestor_count(node) = 1/depth(node). Sum it all up, we get our answer.
*/

#include <bits/stdc++.h>
using namespace std;

int n; 
vector<int> adj[100005];
double ans = 0;

void dfs(int now, int prev, int d) {
	ans += 1.0/d;
	for (auto u: adj[now]) {
		if (u != prev) dfs(u, now, d+1);
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1, 0, 1);

	cout << fixed << setprecision(12) << ans;
	
	return 0;
}