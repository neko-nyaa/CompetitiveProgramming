/*
	https://szkopul.edu.pl/problemset/problem/4CirgBfxbj9tIAS2C7DWCCd7/site/?key=statement
	GCPC 2016 problem C is a near-duplicate of this problem.

	- Looked like a general version of the Frobenius coin problem.
	This is NP-hard, so there's gotta be something else that we can exploit.

	- The low constrain does suggest we can try something like DP in O(NMax). Obviously should not pass.
	This was where I got to, not so far with this.

	- Surprisingly, the way to do this problem is Dijkstra's shortest path.

	- Time limit very tight, had to change from long long to int to pass.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int INF = 1000000007;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<int> dist(50008, INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dist[0] = 0;
	pq.push({0, 0});

	while (pq.size()) {
		auto k = pq.top();
		int now = k.first, w = k.second;
		pq.pop();

		if (dist[now] < w) continue;

		for (int i = 0; i < n; i++) {
			int u = (now + a[i]) % a[0];

			if (dist[u] > a[i] + w) {
				dist[u] = a[i] + w;
				pq.push({u, dist[u]});
			}
		}
	}

	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		if (x == 0 || x >= dist[x % a[0]]) cout << "TAK\n";
		else cout << "NIE\n";
	}

	return 0;
}
