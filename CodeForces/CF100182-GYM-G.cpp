/*
      https://codeforces.com/gym/100812/problem/G

      Solution: https://codeforces.com/blog/entry/21513?#comment-262874
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int n, m;
vector<pair<int, int>> adj[100002];
vector<tuple<int, int, int>> edge;
vector<int> dist(100002, INF);
vector<int> source(100002);
vector<int> start;

void dijkstra() {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

      for (int u: start) {
            dist[u] = 0;
            source[u] = u;
            pq.push({0, u});
      }

      while (pq.size()) {
            auto tmp = pq.top();
            int now = tmp.second, w = tmp.first;
            pq.pop();

            for (auto u: adj[now]) {
                  if (dist[now] + u.second < dist[u.first]) {
                        dist[u.first] = dist[now] + u.second;
                        source[u.first] = source[now];
                        pq.push({dist[u.first], u.first});
                  }
            }
      }
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> m;
      for (int i = 1; i <= n; i++) {
            int dr; cin >> dr;
            if (dr) start.push_back(i);
      }
      for (int i = 0; i < m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            edge.emplace_back(x, y, w);
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
      }
      dijkstra();

      int ans = INF;
      int u = -1, v = -1;

      for (auto [x, y, w]: edge) {
            if (source[x] != source[y] && dist[x] + dist[y] + w < ans) {
                  ans = dist[x] + dist[y] + w;
                  u = source[x], v = source[y];
            }
      }

      if (ans == INF) {
            cout << "No luck at all";
      } else {
            cout << ans << '\n' << u << ' ' << v;
      }

	return 0;
}
