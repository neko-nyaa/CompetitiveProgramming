/*
	https://codeforces.com/problemset/problem/1108/F
	- Tutorial: https://codeforces.com/blog/entry/64751
	This problem shares similarity with 892E.

	- Let's recall Kruskal's algorithm for finding MST. We sort the edges in increasing weight, and connect them in this order with DSU.
	Increasing edge weight by 1 essentially means we can delete this edge. Why this is true will be shown later.

	- For each W such that there is an edge with weight W, let's consider all edges with weight W at once.
	For each of these edges, there are two cases:
		+ They join two vertices that are already connected. In this case, the edge is already useless, ignore it.
		+ They join two vertices that have not been connected. In this case, this edge is potential of being a MST edge.
	- Suppose using these edges, we make K "merge" operations with DSU, then we use up exactly K edges.
	Then we should delete some potential edges so that exactly K potential edges remain.

	- Why is the "delete" operation true? 
	If we increase the weight of a "potential" edge by 1, then in the increased weight, the edge will have joined 2 already connected edges.
	So it will become a useless edge.
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> P, S;
	DSU(int n) {
		P.resize(n+1);
		S.resize(n+1, 1);
		for (int i = 1; i <= n; i++) P[i] = i;
	}

	int find(int x) {
		while (x != P[x]) x = P[x];
		return x;
	}

	void merge(int a, int b) {
		a = find(a); b = find(b);
		if (S[a] < S[b]) swap(a, b);

		S[a] += S[b];
		P[b] = a;
	}

	int same(int a, int b) {
		return find(a) == find(b);
	}
};

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m; cin >> n >> m;
	map<int, vector<tuple<int, int>>> e;
	for (int i = 0; i < m; i++) {
		int x, y, z; cin >> x >> y >> w;
		e[w].emplace_back(x, y);
	}

	DSU d(n);
	int ans = 0, cc = n;
	for (auto u: e) {
		if (cc == 1) break;

		int edge = 0;
		for (auto [x, y]: u.second) {
			if (!d.same(x, y)) {
				edge++;
			}
		}

		for (auto [x, y]: u.second) {
			if (!d.same(x, y)) {
				d.merge(x, y);
				edge--;
			}
		}

		ans += edge;
	}

	cout << ans;
}
