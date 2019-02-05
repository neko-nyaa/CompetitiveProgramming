/*
	https://vjudge.net/problem/UVALive-7903
	https://codeforces.com/gym/101194/problem/G

	- This code works on C++17 thanks to structured bindings. To make it work for older versions, replace auto [x, y] with tie(x, y).

	- Let's think about how we can solve this problem when it's offline. Mr.Panda can pick a flower when he can get there using edges no more than w.
	Therefore we can reduce the input graph into its minimum spanning tree and the connectivity doesn't change.

	- Let's use Kruskal's algorithm to find the minimum spanning tree, maintaining the most common flower for each connected component.
	To merge the flowers of two components together, we merge the smaller component into the larger component every time.
	This is the "small-to-large" merging trick, and in fact merging N times will take at most O(NlogN) time.

	- We can answer queries offline by sorting them in increasing W, then merging as we run Kruskal. This takes a simple DSU modification.

	- Yet now we must solve this problem online. We can simply use a persistent DSU to find the correct DSU version to answer.
	Persistent DSU is we simply exploit the fact that very little changes are made, so we create a "version history" array for each element, instead of modifying things directly.
	To query for a version, we binary search on the history to find the closest up-to-date version to what we need.
	See implementation for better understanding.
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 100005;
#define mp make_pair

struct persistent_DSU {

	int n, version;

	vector<pair<int, int>> parent[maxN];
	vector<int> size;

	vector<pair<int, int>> ans_freq[maxN];
	vector<pair<int, int>> ans_col[maxN];

	map<int, int> color[maxN];

	persistent_DSU() {}

	persistent_DSU(int n, vector<int> c) {
		this->n = n; version = 0;	// intially, it's at version 0
		size.resize(n+1);

		for (int i = 1; i <= n; i++) {
			parent[i].emplace_back(version, i);
			size[i] = 1;

			ans_freq[i].emplace_back(version, 1);
			ans_col[i].emplace_back(version, c[i]);

			color[i][c[i]] = 1;
		}
	}

	int get_root(int u, int ver) {
		auto [v, par] = *(upper_bound(parent[u].begin(), parent[u].end(), mp(ver+1, 0)) - 1);

		if (par != u) {
			return get_root(par, ver);
		} else {
			return par;
		}
	}

	int merge(int u, int v) {
		u = get_root(u, version);
		v = get_root(v, version);

		if (u == v) {
			return 0;
		}

		version++;
		
		if (size[u] > size[v]) swap(u, v);
		parent[u].push_back(mp(version, v));
		size[v] += size[u];

		int cnt;
		int freq_cur = ans_freq[v].back().second;
		int col_cur = ans_col[v].back().second;

		for (auto [col, freq]: color[u]) {
			color[v][col] += freq;

			cnt = color[v][col];

			if (cnt > freq_cur || (cnt == freq_cur && col < col_cur)) {
				freq_cur = cnt;
				col_cur = col;
			}
		}

		ans_freq[v].push_back(mp(version, freq_cur));
		ans_col[v].push_back(mp(version, col_cur));

		color[u].clear();

		return version;
	}

	int query(int u, int ver) {
		u = get_root(u, ver);
		auto [v, col] = *(upper_bound(ans_col[u].begin(), ans_col[u].end(), mp(ver+1, 0)) - 1);

		return col;
	}

} PD;

int n, m;
vector<tuple<int, int, int>> edge;
vector<int> c;

void input() {
	cin >> n >> m;
	c.resize(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}

	edge.clear();
	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w;
		edge.emplace_back(w, u, v);
	}

	PD = persistent_DSU(n, c);
}

vector<int> mst;

void solve() {
	mst.resize(1);			// 1-index is easier
	sort(edge.begin(), edge.end());

	for (auto [w, u, v]: edge) {
		if (PD.merge(u, v)) {
			mst.push_back(w);
		}
	}
}

void answer() {
	int q; cin >> q; int last = 0;
	while (q--) {
		int u, w; cin >> u >> w;
		u ^= last; w ^= last;

		int ver = upper_bound(mst.begin(), mst.end(), w) - mst.begin() - 1;
		last = PD.query(u, ver);

		cout << last << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ":\n";
		input();
		solve();
		answer();
	}	

	return 0;
}