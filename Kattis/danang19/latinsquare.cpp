/*
	- Let's fill in numbers one by one.

	- To fill in one number, let's build a bipartite graph with 2*N vertices:
		+ Left side has N vertices, each corresponding to a row.
		+ Right side has N vertices, each corresponding to a column.
		+ There is an edge between i and j iff grid[i, j] is not filled (equal to 0).
	- If it is possible to fill all instances of a single number in, then the perfect matching on this graph tells us the answer.

	- It turns out that it is always possible to fill in all numbers.
	It can be proven with Hall's theorem, but during contest just having faith is enough.
*/

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

int t = 0;
vector<int> assigned(101, 0);
vector<int> vis(101);
vector<vector<int>> adj(101);

int visit(int u) {
	if (vis[u] != t) {vis[u] = t;}
	else return 0;

	for (int v: adj[u]) {
		if (!assigned[v] || visit(assigned[v])) {
			assigned[v] = u;
			return 1;
		}
	}
	return 0;
}

void solve() {
	int n, k; cin >> n >> k;
	vector<vector<int>> a(n+1, vector<int>(n+1));
	vector<int> has(n+1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			has[a[i][j]] = 1;
		}
	}

	for (int d = 1; d <= n; d++) {
		if (has[d]) continue;

		for (int i = 1; i <= n; i++) {
			assigned[i] = vis[i] = 0;
			adj[i].clear();
		}
		t = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!a[i][j]) adj[i].push_back(j);
			}
		}

		for (int i = 1; i <= n; i++) {
			t++; visit(i);
		}

		for (int i = 1; i <= n; i++) {
			a[assigned[i]][i] = d;
		}
	}

	cout << "YES\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0);

	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}