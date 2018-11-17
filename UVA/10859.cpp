/*
      https://vjudge.net/problem/UVA-10859

      *******          https://csacademy.com/app/graph_editor/
      *******          Helps greatly in visualization

      - Minimum vertex cover on tree!!! This can be done with a dynamic programming solution.
      This time we need more than just minimum cover, we also need maximum double-covered edges.

      - Note that our graph is a forest, so it might be disconnected. So just solve for each component separately. Let's solve the MVC problem first.

      - Let's start from a root and DFS down. When we reach a node, we can either light it up, or not light it up.
      Let's call the node we are at "now", and its children "u":
            + If we decide not to light up "now", then we must light all of its children  --> DP(now, not_light) = sum of: DP(u, light).
            + If we decide to light up "now", then we can light or not light its children --> DP(now, light) = sum of: min(DP(u, light), DP(u, not_light)).
      Answer is now minimum of DP(root, light) and DP(root, not_light).

      - We have minimized the vertex cover. But what about the double edge covers?

      - Let's keep another DP_2, this time for the maximum double edge. When we reach vertex "now", with children "u":
            + If we decide not to light up "now" ---> DP_2(now, not_light) = sum of: DP_2(u, light)
            + If we decide to light up "now" ---> we should choose the option that minimizes DP(u, X), while maximizing DP_2(u, X).
              Note that if we light up both "now" and "u", our double-cover count increases by 1.
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[1001];
int dp[2][1001];
int dp2[2][1001];
vector<int> vis(1001);

void input() {
      fill(vis.begin(), vis.end(), 0);
      cin >> n >> m;
      for (int i = 0; i < n; i++) {
            adj[i].clear();
      }
      memset(dp, 0, sizeof(dp));
      memset(dp2, 0, sizeof(dp2));

      for (int i = 0; i < m; i++) {
            int x, y; cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
      }
}

void dfs(int now) {
      vis[now] = 1;
      dp[1][now] = 1;
      for (int u: adj[now]) {
            if (!vis[u]) {
                  dfs(u);

                  dp[0][now] += dp[1][u];
                  dp2[0][now] += dp2[1][u];

                  if (dp[1][u] < dp[0][u]) {
                        dp2[1][now] += dp2[1][u] + 1;
                        dp[1][now] += dp[1][u];
                  } else if (dp[1][u] > dp[0][u]) {
                        dp2[1][now] += dp2[0][u];
                        dp[1][now] += dp[0][u];
                  } else {
                        dp2[1][now] += max(dp2[1][u] + 1, dp2[0][u]);
                        dp[1][now] += dp[1][u];
                  }
            }
      }
}

void solve() {
      int mvc = 0, double_lamppost = 0;
      for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                  dfs(i);

                  if (dp[1][i] == dp[0][i]) {
                        mvc += dp[1][i];
                        double_lamppost += max(dp2[0][i], dp2[1][i]);
                  } else if (dp[1][i] < dp[0][i]) {
                        mvc += dp[1][i];
                        double_lamppost += dp2[1][i];
                  } else {
                        mvc += dp[0][i];
                        double_lamppost += dp2[0][i];
                  }
            }
      }
      cout << mvc << ' ' << double_lamppost << ' ' << m - double_lamppost << '\n';
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
