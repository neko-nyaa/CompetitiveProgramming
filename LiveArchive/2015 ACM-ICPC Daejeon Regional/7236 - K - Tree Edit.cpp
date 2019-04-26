/*
	- Tree T1 and T2 are renamed into tree S and tree T, for the sake of the implementation.

	- We want to transform tree S into tree T, and we can perform the following operations:
		+ Rename a node
		+ Delete a leaf
		+ Insert a leaf
	- Let's put an index on each of the nodes in each tree, then we can rephrase the operations as follow:
		+ Rename a node, cost 1
		+ Delete a subtree u, cost subtree_size(u)
		+ Insert a subtree, cost new_subtree_size()
	- Define a function TED(s, t) as the edit distance between the subtree of S rooted at s, and similarly for T.
		---> We want to find TED(root_S, root_T);
	- We can apply the same "string edit distance" DP for each TED(s, t), using these operations:
	  	+ Delete any subtree rooted at u, such that u is a direct children of s. 
	  	  The cost is S_subtree_size(u).
	  	+ Insert any subtree and attach it into s. 
	  	  The cost is the size of the subtree.
	  	+ For any two nodes u and v, such that u is a direct children of s, and v is a direct children of t, modify the subtree of u so that it matches v.
	  	  The cost is TED(u, v).
	- Apply the edit distance problem into each subtree, and we find our answer.
*/

#include <bits/stdc++.h>
using namespace std;

struct tree{
	int n;
	vector<vector<int>> adj;
	vector<char> c;
	vector<int> subtr;

	tree() {}

	tree(string s) {
		vector<pair<int, char>> k = parse(s);
		this->n = k.size();
		subtr.resize(n);
		adj.resize(n);

		for (int i = 0; i < k.size(); i++) {
			if (k[i].first != -1) {
				adj[k[i].first].push_back(i);
			}
			c.push_back(k[i].second);
		}

		predfs(0);
	}

	vector<pair<int, char>> parse(string s) {
		s.erase(0, 1); s.pop_back();
		vector<pair<int, char>> ans;

		stack<pair<int, int>> st;
		int par = -1, cur = 0, cnt = 0;

		for (char c: s) {
			if (c == '(') {
				st.push({par, cur});
				par = cur;
				cur = cnt;
			} else if (isalnum(c)) {
				cnt++;
				ans.emplace_back(par, c); 
			} else if (c == ')') {
				par = st.top().first;
				cur = st.top().second;
				st.pop();
			}
		}

		return ans;
	}

	void predfs(int now) {
		subtr[now] = 1;
		for (int u: adj[now]) {
			predfs(u);
			subtr[now] += subtr[u];
		}
	}
}s, t;

int ed_dist[1000][1000];

int edit_distance(int nows, int nowt);
int edit_string(vector<int> sc, vector<int> tc);

void input() {
	string sstr, tstr;
	cin >> sstr >> tstr;

	s = tree(sstr);
	t = tree(tstr);

	for (int i = 0; i < s.n; i++) {
		for (int j = 0; j < t.n; j++) {
			ed_dist[i][j] = -1;
		}
	}
}

void solve() {
	cout << edit_distance(0, 0) << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	while (t--) {
		input();
		solve();
	}
	
	return 0;
}

int edit_distance(int nows, int nowt) {
	if (ed_dist[nows][nowt] != -1) {
		return ed_dist[nows][nowt];
	}

	vector<int> sc, st;
	for (auto u: s.adj[nows]) {
		sc.push_back(u);
	}
	for (auto u: t.adj[nowt]) {
		st.push_back(u);
	}

	return ed_dist[nows][nowt] = edit_string(sc, st) + (s.c[nows] != t.c[nowt]);
}	

int edit_string(vector<int> sc, vector<int> tc) {
	int n = sc.size(), m = tc.size();
	vector<vector<int>> dp(n+1, vector<int>(m+1));

	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i-1][0] + s.subtr[sc[i-1]];
	}
	for (int i = 1; i <= m; i++) {
		dp[0][i] = dp[0][i-1] + t.subtr[tc[i-1]];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = min(dp[i-1][j] + s.subtr[sc[i-1]], dp[i][j-1] + t.subtr[tc[j-1]]);
			dp[i][j] = min(dp[i][j], dp[i-1][j-1] + edit_distance(sc[i-1], tc[j-1]));
		}
	}

	return dp[n][m];
}