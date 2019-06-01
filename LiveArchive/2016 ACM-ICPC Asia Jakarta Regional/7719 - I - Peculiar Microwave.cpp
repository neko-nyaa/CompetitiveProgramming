/*
	- The first thing that's easy to notice is that there must be an answer in the range [E, E + 1000]

	- Suppose we can reach X seconds for any positive X
	  Then we can reach X + K*P[1] for any non-negative K (just push the first button K times lol)

	- We are given an array P[]. Let's build a graph with P[1] nodes, numbered from 0 to P[1] - 1.
	  There is an edge [U, (U + P[i]) mod P[1]] with cost P[i] for every 0 <= U < P[1] and 2 <= i <= N
	
	- The obvious case is that we can reach 0 seconds using 0 pushes.
	  Let's find the shortest path from node 0 to every other nodes. 
	  Then, the shortest path from 0 to U is equal to the minimum reachable number X, such that X mod P[1] = U.

	- Now just check for every E in range [E, E + 1000] to see if it's possible to reach E.
*/	

#include <bits/stdc++.h>
using namespace std;

const int INF = 1000001008;

void solve() {
	int n, e; cin >> n >> e;
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	vector<int> dist(p[0], INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[0] = 0;
	pq.push({0, 0});

	while (pq.size()) {
		auto k = pq.top();
		int now = k.first, w = k.second;
		pq.pop();

		if (dist[now] < w) continue;

		for (int i = 0; i < n; i++) {
			int u = (now + p[i]) % p[0];

			if (dist[u] > p[i] + w) {
				dist[u] = p[i] + w;
				pq.push({u, dist[u]});
			}
		}
	}

	for (int i = e; ; i++) {
		if (i >= dist[i % p[0]]) {
			cout << i - e << '\n';
			return;
		}
 	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
	
	return 0;
}