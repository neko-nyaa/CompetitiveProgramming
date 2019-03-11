/*
	https://codeforces.com/gym/101620/problem/G
	Presentation of solutions: http://cerc.hsin.hr/tasks/cerc2017_presentation.pdf

	- If we consider paths from 1 to N, we will have to consider so many paths.
	And there are so many factors in each step as well, we can't really do it can't we? :)

	- Let's do the opposite: let's solve from N back to 1.

	- Define f(X) as the expected turns to reach node N from node X. Then we have f(N) = 0.

	- What's the optimal strategy here? 
	Suppose we are at node X, and the ticket purchased gets us to node Y. 
	Then it's only optimal to get to Y if f(Y) < f(X). Otherwise we stay at X.

	- Now we can find the formula for f(X):
	f(X) = (expected number of coins until we use a ticket)*(sum of expectations of f(Y) such that f(Y) < f(X))
	Let cnt[X] be the number of nodes Y adjacent to X such that f(Y) < f(X), then we have
	f(X) = degree[X]/cnt[X] + (sum of all f(Y))/cnt[X];

	It is easier to see this if you take any correct code, and print all f(X).

	- We can use a priority queue to maintain the minimum calculated f(X), and update f(U) for every U adjacent to X.
	So we end up with a solution very similar to Dijkstra's shortest path algorithm!!!!
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const double INF = 1e18;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

int n, m;
vector<int> adj[300001];
vector<double> ans(300001, INF);

vector<int> deg(300001);
vector<double> cnt(300001);
vector<double> sum(300001);

vector<int> vis(300001);

void dijkstra() {
	min_heap<pair<double, int>> pq;

	ans[n] = 0; pq.push({0, n});

	while (pq.size()) {
		auto [w, now] = pq.top(); 
		pq.pop();

		if (vis[now]) continue;
		vis[now] = 1;

		for (auto u: adj[now]) {
			if (vis[u]) continue;

			cnt[u]++;
			sum[u] += ans[now];

			ans[u] = (deg[u] + sum[u])/cnt[u];
			pq.push({ans[u], u});
		}
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> m;
	while (m--) {
		int x, y; cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
		deg[x]++; deg[y]++;
	}

	dijkstra();

	cout << fixed << setprecision(12) << ans[1];

	return 0;
}
