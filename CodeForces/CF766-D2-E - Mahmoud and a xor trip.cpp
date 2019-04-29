/*
	https://codeforces.com/contest/766/problem/E

	- We can solve this with centroid decomposition.

	--------------------------------------------------------------------------

	- Let's root the tree at its centroid. Now let's answer this question:
		"What is the sum of all the paths that goes through the root(centroid)?"

	- We can obtain every path from the root to the other nodes with a DFS.
	  Now every valid path that goes through the centroid as we need meets any of these conditions:
	  	+ The path contains a single node that is the centroid (1)
	  	+ The path starts from the centroid, and ends at arbitrary non-centroid node. (2)
	  	+ The path is a concatenation of two paths from (2), such that their LCA is root.

	- To solve this question, for every node u adjacent to the centroid, we group all paths that goes from root, and goes through u.
	  Then we answer the question:
	  	"What is the sum of all xor pairs (X xor Y) in this set of paths, such that X and Y belong to different groups?"
	  This is possible in O(N), we process groups one by one, maintaining the bit count at each position of the groups we went through so far.
	  Don't forget to xor each pair by a[centroid] also (so we actually need X xor Y xor a[centroid]).

	- We have obtained the answer for every possible path that goes through centroid, but what about paths that do not go through centroid?

	- We can delete the centroid when we finished solving, 
	  and for every subtree that the deleted centroid separates, we find the new tree's centroid and solve this all over again, ignoring destroyed nodes.

	--------------------------------------------------------------------------

	- Our centroid tree has a height of at most log(N), therefore each node participates in at most log(N) solvings.
	We obtain a solution with time complexity of O(NlogN).
*/

#include <bits/stdc++.h>
using namespace std;

int n, a[100005]; 
vector<int> adj[100005];
vector<int> solved(100005);
vector<int> subtr(100005);
long long ans;

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; ans += a[i];
	}
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
}

// for finding centroids

int find_subtr_size(int now, int prev) {
	int ans = 1;
	for (int u: adj[now]) {
		if (u != prev && !solved[u]) {
			ans += find_subtr_size(u, now);
		}
	}
	return subtr[now] = ans;
}

int dfsc(int now, int prev, int sz) {
	for (int u: adj[now]) {
		if (u != prev && !solved[u] && subtr[u] > (sz)/2) {
			return dfsc(u, now, sz);
		}
	}
	return now;
}

int find_centroid(int now, int prev) {
	int sz = find_subtr_size(now, prev);
	int centroid = dfsc(now, prev, sz);
	solved[centroid] = 1;
	return centroid;
}

// for solving

void dfsp(int now, int prev, int xr, vector<int> &path) {
	path.push_back(xr);
	for (int u: adj[now]) {
		if (!solved[u] && u != prev) {
			dfsp(u, now, xr ^ a[u], path);
		}
	}
}

void solve_centroid(int centroid) {
	vector<vector<int>> paths;

	for (int u: adj[centroid]) {
		if (!solved[u]) {
			vector<int> path_u;
			dfsp(u, centroid, a[u], path_u);
			paths.push_back(path_u);
		}
	}

	vector<int> o(20), z(20);
	for (auto v: paths) {
		for (int i: v) {
			ans += i^a[centroid];

			for (int b = 0; b < 20; b++) {
				if ((i^a[centroid]) & (1 << b)) {
					ans += z[b] * (1LL << b);
				} else {
					ans += o[b] * (1LL << b);
				}
			}
		}
		for (int i: v) {
			for (int b = 0; b < 20; b++) {
				if (i & (1 << b)) {
					o[b]++;
				} else {
					z[b]++;
				}
			}
		}
	}

	for (int u: adj[centroid]) {
		if (!solved[u]) {
			int ct = find_centroid(u, centroid);
			solve_centroid(ct);
		}
	}
}

void solve() {
	int ct = find_centroid(1, 0);
	solve_centroid(ct);
	cout << ans;
}


signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	input();
	solve();
	
	return 0;
}