/*
	- Add two nodes into graph, node 0 and node n+1
	- For each edge in graph, add flow edge with cost 1 and capacity INF
	- For each black coin at node u, add flow from 0 to u edge with cost 0 capacity 1 
	- For each black node u, add flow from u to n+1 edge with cost 0 capacity 1 
	- Answer is simply min-cost max-flow from 0 to n+1
*/

#include <bits/extc++.h>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

struct MCMF {
	int N;
	vector<vector<int>> ed, red;
	vector<vector<long long>> cap, flow, cost;
	vector<int> seen;
	vector<long long> dist, pi;
	vector<pair<int, int>> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, vector<long long>(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, long long cap, long long cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(seen.begin(), seen.end(), 0);
		fill(dist.begin(), dist.end(), INF);
		dist[s] = 0; long long di;

		__gnu_pbds::priority_queue<pair<long long, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, long long cap, long long cost, int dir) {
			long long val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (auto &i: ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (auto &i: red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		for (int i = 0; i < N; i++) {
			pi[i] = min(pi[i] + dist[i], INF);
		} 
	}

	pair<long long, long long> maxflow(int s, int t) {
		long long totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			long long fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				totcost += cost[i][j] * flow[i][j];
			} 
		} 
		return {totflow, totcost};
	}
};

void solve() {
	int n, m; cin >> n >> m;
	// nodes numbered 1 to N
	// source is 0, sink is N+1

	MCMF mf(n+2);
	while (m--) {
		int u, v; cin >> u >> v;
		mf.addEdge(u, v, 600, 1);
		mf.addEdge(v, u, 600, 1);
	}

	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (x) {
			mf.addEdge(0, i, 1, 0);
		}
	}
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (x) {
			mf.addEdge(i, n+1, 1, 0);
		}
	}

	cout << mf.maxflow(0, n+1).second << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) solve();

	return 0;
}