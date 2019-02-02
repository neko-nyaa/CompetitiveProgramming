/*
	https://codeforces.com/contest/892/problem/E
	Tutorial: https://codeforces.com/blog/entry/55841

	- This problem is more tricky on implementation than on idea. This code is very inefficient as well :( it runs in 1996ms

	- Suppose given a list of edges of the same weight W, how do we know if they can all belong to a MST?

	- Let's recall Kruskal's algorithm. We sort the weights in increasing order, and join them in order with DSU.
	For a list of edges of weight W, they can all belong to MST if they can form a "under construction MST".
	Here "under construction MST" for weight W is defined as Kruskal's algorithm applied on all edges weight lower than W, which may have created a forest.

	- We will solve this problem offline. Let's process the list of edges in increasing order or weight. 
	For each query, we will check if these edges, if they are in the query, form a cycle in the incomplete MST or not.
	When we're done we will merge edges of said weight, much like normal Kruskal's.

	- Implementation of this is quite tricky. 
	The easiest way I came up with is to use two DSUs, the first for constructing the partial MST, the second for checking cycles.

	- This is a good code as well, in my opinion.
	https://codeforces.com/contest/892/submission/32401257
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> P, S;
	set<int> st;
	DSU(int n) {
		P.resize(n+1);
		S.resize(n+1, 1);
		for (int i = 1; i <= n; i++) P[i] = i;
	}

	int find(int x) {
		while (x != P[x]) x = P[x];
		return x;
	}

	void reset() {
		for (int i: st) {
			P[i] = i;
			S[i] = 1;
		}
		st.clear();
	}

	void merge(int a, int b) {
		st.insert(a); st.insert(b);

		a = find(a); b = find(b);
		if (a == b) return;
		if (S[a] < S[b]) swap(a, b);

		S[a] += S[b];
		P[b] = a;
	}

	int same(int a, int b) {
		return find(a) == find(b);
	}
} d1(500005), d2(500005);

int n, m, q;
vector<tuple<int, int, int>> edge;
map<int, vector<tuple<int, int, int>>> queries;
map<int, vector<tuple<int, int>>> mst;
vector<int> ans(500005, 1);

void solve(vector<tuple<int, int, int>> edges) {
	map<int, vector<tuple<int, int>>> tmp;
	for (auto [i, x, y]: edges) {
		tmp[i].emplace_back(x, y);
	}

	for (auto [i, e]: tmp) {
		d2.reset();

		for (auto [x, y]: e) {
			x = d1.find(x); y = d1.find(y);

			if (d2.same(x, y)) {
				ans[i] = 0; break;
			}
			d2.merge(x, y);
		}
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		edge.emplace_back(w, x, y);
		mst[w].emplace_back(x, y);
	}

	cin >> q;
	for (int i = 0; i < q; i++) {
		int k; cin >> k;
		while (k--) {
			int u; cin >> u; u--;

			auto [w, x, y] = edge[u];
			queries[w].emplace_back(i, x, y);
		}
	}

	for (auto [w, edges]: mst) {
		solve(queries[w]);

		for (auto [x, y]: edges) {
			d1.merge(x, y);
		}
	}

	for (int i = 0; i < q; i++) {
		cout << (ans[i] ? "YES\n" : "NO\n");
	}

	return 0;
}
