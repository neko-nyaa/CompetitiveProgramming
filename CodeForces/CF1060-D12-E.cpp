/*
      https://codeforces.com/contest/1060/problem/E

      - Let's see what happens to a path in the tree, when the new edges are added.

      - Each node of distance 2 is now added an edge, and their distance becomes 1.

      - So now every distance in the tree is halved, due to each pair of node being shortened.

      - Problem becomes "calculate all dist(i, j)/2 rounded up for each pair of nodes".

      - The answer is ((sum of all distances) + (number of odd-length paths))/2.
      The latter part of the formula was added so that each odd paths are rounded.

*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, ans, o, e;
vector<vector<int>> adj(200008);
vector<int> subtr(200008, 1);

void dfs(int now, int prev, int d = 0) {
      if (d) o++;
      else e++;
      for (int u: adj[now]) {
            if (u != prev) {
                  dfs(u, now, d^1);
                  subtr[now] += subtr[u];
            }
      }
      ans += subtr[now] * (n - subtr[now]);
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      cin >> n;
      if (n == 1) {cout << 0; return 0;}
      for (int i = 1; i < n; i++) {
            int x, y; cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
      }
      dfs(1, 0);

      cout << (ans + o*e)/2;

	return 0;
}
