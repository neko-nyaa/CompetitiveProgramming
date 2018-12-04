/*
      https://vjudge.net/problem/UVA-11765

      - This is a cool variant of min-cut problem.

      - We have N components. For each component, denote the cost of placing it on top and bottom as top[i] and bottom[i], respectively.
      If a component can't be placed somewhere, we can assume they can be placed with a cost of infinity.

      - Let's model a flow network as following:
            + We will add two extra nodes, node 0 for the source, and node N+1 for the sink.
            + For each component, there is an edge with capacity top[i] from 0 to i, and bottom[i] from i to N+1.
            + For each interconnection, there is an edge from p to q, and from q to p, both with capacity r.

      - The answer is now the minimum cut of the network. If we model the circuit board as a bipartite graph, it is easy to see this is the case.
      By the min-cut max-flow theorem, the minimum cut is equal to the maximum flow of the network.
      So all we have to do now is to send a maximum flow from node 0 to node N+1.

      - Both Dinic's and Edmonds-Karp's work well on this problem. This code uses the former, but you can use any you like.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Flow {
	int n;
	vector<vector<int>> adj;
	vector<vector<int>> capacity;

	Flow() {}
	Flow(int n) {
		this->n = n;
		adj.resize(n+1);
		capacity.resize(n+1, vector<int>(n+1));
	}

	void add_edge(int u, int v, int c) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		capacity[u][v] = c;
	}

	int bfs(int s, int t, vector<int> &parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;

		queue<pair<int, int>> q;
		q.push({s, 1e9});

		while (!q.empty()) {
			int cur = q.front().first;
			int flow = q.front().second;
			q.pop();

			for (int next: adj[cur]) {
				if (parent[next] == -1 && capacity[cur][next]) {
					parent[next] = cur;
					int new_flow = min(flow, capacity[cur][next]);

					if (next == t) return new_flow;

					q.push({next, new_flow});
				}
			}
		}

		return 0;
	}

	int max_flow(int s, int t) {
		int flow = 0;
		vector<int> parent(n+1);
		int new_flow;

		while (new_flow = bfs(s, t, parent)) {
			flow += new_flow;

			int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= new_flow;
				capacity[cur][prev] += new_flow;

				cur = prev;
			}
		}

		return flow;
	}
};

const int INF = 1e9;

int n, m;
vector<int> top, bottom;

void solve() {
      cin >> n >> m; top.resize(n+1); bottom.resize(n+1);
      for (int i = 1; i <= n; i++) cin >> top[i];
      for (int i = 1; i <= n; i++) cin >> bottom[i];

      Flow F(n+1);

      for (int i = 1; i <= n; i++) {
            int x; cin >> x;

            if (x == 1) {
                  bottom[i] = INF;
            } else if (x == -1) {
                  top[i] = INF;
            }

            F.add_edge(0, i, top[i]);
            F.add_edge(i, n+1, bottom[i]);
      }

      for (int i = 1; i <= m; i++) {
            int u, v, w; cin >> u >> v >> w;
            F.add_edge(u, v, w);
            F.add_edge(v, u, w);
      }

      cout << F.max_flow(0, n+1) << '\n';
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int t; cin >> t;
      while (t--) {
            solve();
      }

      return 0;
}
