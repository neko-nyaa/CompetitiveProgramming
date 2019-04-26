/*
	- Bipartite grid. Black and white. Flow network.
	- Add edge from source to black squares, capacity a[i][j]
	- Add edge from white squares to sink, capacity a[i][j]
	- Add edge for connected black and whites, capacity INF
	- Answer = sum of matrix - maxflow
*/

#include <bits/extc++.h>
using namespace std;

struct Edge {
	int u, v;
	int capacity;
	int flow;
};

struct Flow {
	int n;
	int source, sink;

	vector<vector<int>> a;
	vector<Edge> E;

	vector<int> cur;
	vector<int> dist;

	Flow();
	Flow(int n, int s, int t) {
		this->n = n;
		source = s; sink = t;
		a.resize(n+1);
		cur.resize(n+1);
		dist.resize(n+1);
	}

	void add_edge(int u, int v, int c) {
		a[u].push_back(E.size());	E.push_back({u, v, c, 0});
		a[v].push_back(E.size());	E.push_back({v, u, 0, 0});
	}

	int bfs() {
		fill(dist.begin(), dist.end(), -1);

		queue<int> Q;
		Q.push(source); dist[source] = 0;

		while (!Q.empty()) {
			int u = Q.front(); Q.pop();

			for (int i = 0; i < a[u].size(); i++) {
				int id = a[u][i];
				int v = E[id].v;

				if (dist[v] < 0 && E[id].flow < E[id].capacity) {
					dist[v] = dist[u] + 1;
					Q.push(v);
				}
			}
		}

		return dist[sink] >= 0;
	}

	int dfs(int now, int flow) {
		if (flow == 0) return 0;
		if (now == sink) return flow;

		for (; cur[now] < a[now].size(); cur[now]++) {
			int id = a[now][cur[now]];
			int v = E[id].v;

			if (dist[v] == dist[now] + 1) {
				int delta = dfs(v, min(flow, E[id].capacity - E[id].flow));
				if (delta) {
					E[id].flow += delta;
					E[id^1].flow -= delta;

					return delta;
				}
			}
		}

		return 0;
	}

	int maxflow() {
		int ans = 0;
		while (bfs()) {
			fill(cur.begin(), cur.end(), 0);
			while (1) {
				int delta = dfs(source, 1e9);
				if (!delta) break;

				ans += delta;
			}
		}

		return ans;
	}
};

int a[51][51];
int dc[51][51];

void solve() {
	int n, m; cin >> n >> m;
	Flow b(n*m + 1, 0, n*m + 1);

	int k = 0; int s = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			s += a[i][j];
			
			k++;
			dc[i][j] = k;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i + j) % 2) {
				b.add_edge(0, dc[i][j], a[i][j]);
			} else {
				b.add_edge(dc[i][j], n*m + 1, a[i][j]);
			}
			
			if ((i + j) % 2) {
				int x = i+1, y = j;
				if (x <= n) {
					b.add_edge(dc[i][j], dc[x][y], 1000000000);
				}
	
				x = i, y = j+1;
				if (y <= m) {
					b.add_edge(dc[i][j], dc[x][y], 1000000000);
				}
				
				x = i-1, y = j;
				if (x) {
					b.add_edge(dc[i][j], dc[x][y], 1000000000);
				}
	
				x = i, y = j-1;
				if (y) {
					b.add_edge(dc[i][j], dc[x][y], 1000000000);
				}
			}
		}
	}

	cout << s - b.maxflow() << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}