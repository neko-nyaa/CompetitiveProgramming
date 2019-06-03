/*
	https://codeforces.com/gym/101174 problem F

	- We are given a tree, each node have a parameter r[i] and t[i]. We want to answer:
		"For each node i, what is the sum of all t[u] such that u is in the subtree of i, and r[u] < r[i]"

	- We will process the nodes in increasing order of r. 

	- Let's initially set all t[i] of the nodes to 0. We need to support these two operations:
		+ Update t[u] of some node u.
		+ Query sum of all t in the subtree of some node u.

	- This is easy, let's build a DFS order array of this tree.
	  Let's also maintain in[u] and out[u], being the entry and exit time of node[u] when we DFS.
	  The subtree of node u is simply the subarray between in[u] and out[u] in the DFS order array.

	- So we can just maintain a fenwick tree to do subarray sum query.

	- There's a little easter egg in my fenwick :) see if you can spot that 
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct johnwick_tree{
	int n;
	vector<long long> tree;

	johnwick_tree(int n) {
		this->n = n;
		tree.resize(n+3);
	}

	void update(int p, long long val){
		for (int i = p; i <= n; i += i & -i) {
			tree[i] += val;
		}
	}
	
	long long sum(int p) {
		long long ans = 0;
		for (int i = p; i; i -= i & -i) {
			ans += tree[i];
		}
		return ans;
	}
};

int n;
vector<int> adj[100001];
vector<int> in(100001);
vector<int> out(100001);
vector<int> t(100001);
map<int, vector<int>> r;

vector<int> ind(100001);
vector<int> ans(100001);

johnwick_tree fw(100001);

void dfs(int now, int &tm) {
	in[now] = ++tm;
	ind[now] = tm;

	for (int i: adj[now]) {
		dfs(i, tm);
	}

	out[now] = tm;
}

void solve(vector<int> nd) {
	for (int i: nd) {
		ans[i] = fw.sum(out[i]) - fw.sum(in[i] - 1);
	}

	for (int i: nd) {
		fw.update(ind[i], t[i]);
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n; int root = 0;
	for (int i = 1; i <= n; i++) {
		int p, rank; 
		cin >> p >> rank >> t[i];
		r[rank].push_back(i);

		if (p == -1) root = i;
		else adj[p].push_back(i);
	}

	int tm = 0;
	dfs(root, tm);

	for (auto u: r) {
		solve(u.second);
	}

	for (int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}