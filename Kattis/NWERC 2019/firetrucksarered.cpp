#include <bits/stdc++.h>
using namespace std;

struct DSU{
	vector<int> P, S;

	DSU (int n) {
		P.resize(n+1);
		for (int i = 1; i <= n; i++) {
			P[i] = i;
		}
		S.resize(n+1, 1);
	}

	int find(int x) {
		while (x != P[x]) x = P[x];
		return x;
	}

	int same(int u, int v) {
		return find(u) == find(v);
	}

	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;

		if (S[u] > S[v]) swap(u, v);
		S[v] += S[u];
		P[u] = v;
	}
};

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	int n; cin >> n;
	map<int, vector<int>> m;
	for (int i = 1; i <= n; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			m[x].push_back(i);
		}
	}

	vector<tuple<int, int, int>> ans;
	DSU d(n);
	for (auto [u, v]: m) {
		for (int i = 1; i < v.size(); i++) {
			if (!d.same(v[i], v[i-1])) {
				d.merge(v[i], v[i-1]);
				ans.emplace_back(v[i], v[i-1], u);
			}
		}
	}

	if (ans.size() != n-1) {
		cout << "impossible\n";
	} else {
		for (auto [u, v, w]: ans) cout << u << ' ' << v << ' ' << w << '\n';
	}
 
	return 0;
}