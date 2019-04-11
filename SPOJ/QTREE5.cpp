/*
	https://www.spoj.com/problems/QTREE5/ 

	- This is a rather hectic problem. But probably a classic on centroid decomposition.

	- Okay, so of course we know this problem is centroid decomp. But how to apply so?

	- Here is a good tutorial on centroid decomp:
		https://medium.com/carpanese/an-illustrated-introduction-to-centroid-decomposition-8c1989d53308

	- There are several important characteristic of centroid decomposition that we will be making use of.
	
	- Let's create the centroid decomposition of the input free.
	For simplicity, we will call the input tree TREE, and the centroid decomposition of TREE be CENTREE

	- We will have to store one extra information for each node u in CENTREE:
	For each node u, we keep track of the minimum distance from u to every white node in the subtree of u in CENTREE.
	Call this one MINSUB(u)
	
	- To answer a query for node v, we will find minimum(dist(u, v) in TREE + MINSUB(v)) for each v that is the ancestor of u in CENTREE.

	- Why does this work? Let's notice a few characteristic of centroid decomposition:
		+ The height of CENTREE is at most log(N). Thus the memory complexity of storing every white node in each subtree will be O(NlogN) total.
		  Also we have at most log(N) ancestor of any given node v, thus we only have that much iteration for querying.
		+ Any path(u, v) in TREE can be decomposed into TREEpath(u, LCA(u, v) in CENTREE) + TREEpath(v, LCA(u, v) in CENTREE).
		  Thus we are essentially iterating over this LCA(u, v) in CENTREE, and by maintaining MINSUB we can efficiently find the minimum answer.

	- Let's keep a multiset for each node in the CENTREE, to store the extra information.
	This way we can handle toggle colors easily by inserting/removing distances.
	To find MINSUB(u) for a node u we will just pick the minimum number in the multiset of node u.
*/

#include <bits/stdc++.h>
using namespace std;

struct LowestCommonAncestor{
	int n;
	vector<set<int>> adj;
	vector<int> parent;
	vector<int> level;
	vector<vector<int>> sp;

	LowestCommonAncestor() {}

	LowestCommonAncestor(vector<set<int>> adj) {
		this->n = adj.size() - 1;
		this->adj = adj;

		parent.resize(n+1);
		level.resize(n+1);
		sp.resize(n+1, vector<int>(22, -1));
		dfs(1, 0);
		LCAinit();
	}

	void dfs(int now, int prev) {
		level[now] = level[prev] + 1;
		parent[now] = prev;
		for (auto u: adj[now]) {
			if (u != prev) {
				dfs(u, now);
			}
		}
	}

	void LCAinit() {
		for(int i = 1; i <= n; i++){
			sp[i][0] = parent[i];
		}

		for (int j = 1; (1 << j) < n; j++) {
			for (int i = 1; i <= n; i++) {
				 if(sp[i][j-1] != -1){
					sp[i][j] = sp[sp[i][j-1]][j-1] ;
				}
			}
		}
	}

	int LCA(int u, int v) {
		if (level[u] < level[v]) {
			swap(u, v);
		}

		int dist = level[u] - level[v] ;
		while(dist > 0){
			int raise_by = log2(dist);
			u = sp[u][raise_by];
			dist -= (1 << raise_by) ;
		}
		if(u == v) return u;

		for (int j = 20; j >= 0; j--) {
			if (sp[u][j] != -1 && sp[u][j] != sp[v][j]) {
				u = sp[u][j];
				v = sp[v][j];
			}
		}

		return parent[u]; 
	}

	int dist(int u, int v) {
		return level[u] + level[v] - 2*level[LCA(u, v)];
	}
};

struct CentroidDecomposition {
	int white = 0;
	vector<set<int>> tree;
	vector<int> dad;
	vector<int> sub;
	vector<int> state;
	LowestCommonAncestor lca;

	vector<multiset<int>> dist;

	CentroidDecomposition(vector<set<int>> &tree) : tree(tree) {
		int n = tree.size() - 1;
		dad.resize(n + 1);
		sub.resize(n + 1);
		dist.resize(n + 1);
		state.resize(n + 1);
		lca = LowestCommonAncestor(tree);
		build(1, -1);
	}

	void build(int u, int p) {
		int n = dfs(u, p);
		int centroid = dfs(u, p, n);
		if (p == -1) p = centroid;
		dad[centroid] = p;

		for (auto v : tree[centroid]) {
			tree[centroid].erase(v),
			tree[v].erase(centroid),
			build(v, centroid);
		}
	}

	int dfs(int u, int p) {
		sub[u] = 1;

		for (auto v : tree[u]){
			if (v != p) sub[u] += dfs(v, u);
		}

		return sub[u];
	}

	int dfs(int u, int p, int n) {
		for (auto v : tree[u]) {
			if (v != p and sub[v] > n/2) return dfs(v, u, n);
		}
		return u;
	}

	void toggle(int u) {
		if (state[u]) white--;
		else white++;

		int v = u;
		while (1) {
			if (state[u]) {
				dist[v].erase(dist[v].find(lca.dist(u, v)));
			} else {
				dist[v].insert(lca.dist(u, v));
			}

			if (v == dad[v]) break;
			v = dad[v];
		}
		state[u] ^= 1;
	}

	int query(int u) {
		if (!white) return -1;

		int ans = 10000000;
		int v = u;
		while (1) {
			if (!dist[v].empty()) {
				ans = min(ans, lca.dist(u, v) + *dist[v].begin());
			}

			if (v == dad[v]) break;
			v = dad[v];
		}
		return ans;
	}
};

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n; cin >> n;
	vector<set<int>> adj(n+1);
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		adj[x].insert(y);
		adj[y].insert(x);
	}

	CentroidDecomposition cd(adj);

	int q; cin >> q;
	while (q--) {
		int x, u; cin >> x >> u;
		if (x == 0) {
			cd.toggle(u);
		} else {
			cout << cd.query(u) << '\n';
		}
	}
	
	return 0;
}
