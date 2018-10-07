/*
      https://codeforces.com/gym/101908/problem/L

      - Counting path on tree? This calls for the mighty LCA.

      - Problem summary: given a tree, queries of the form A B C D, count number of common vertices on the path from A to B and from C to D.

      - Might looks simple at first, but actually tricky to come up with the full solution.

      - Let X be lowest common ancestor (LCA) of A and B, Y be the LCA of C and D.
      Now we can break each path down to 2 paths, A X + B X and C Y + D Y. Much easier to work with.

      - We can prove that these common vertices form a path. So instead of counting common vertices, we will count common edges.
      That is, the length of the path intersections.

      - Then the number of common vertices is just number of common edges plus one.

      - Be careful of the case when there are no common edges, then there may or may not be any common vertices at all.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, q;
vector<int> parent(100005);
vector<int> level(100005);
vector<vector<int>> sp(100005, vector<int>(22, -1));
vector<int> adj[100005];

void LCAinit() {
      for(int i = 1; i <= n; i++){
            sp[i][0] = parent[i];
      }

      for (int j = 1; (1 << j) < n; j++) {
            for (int i = 1; i <= n; i++) {
                 if(sp[i][j-1] != -1){
                        sp[i][j] = sp[sp[i][j-1]][j-1] ;
                  }
            }
      }
}

int lca(int u, int v) {
      if (level[u] < level[v]) {
            swap(u, v);
      }

      int dist = level[u] - level[v] ;
      while(dist > 0){
            int raise_by = log2(dist);
            u = sp[u][raise_by];
            dist -= (1 << raise_by) ;
      }
      if(u == v) return u;

      for (int j = 20; j >= 0; j--) {
            if (sp[u][j] != -1 && sp[u][j] != sp[v][j]) {
                  u = sp[u][j];
                  v = sp[v][j];
            }
      }

      return parent[u];
}

void dfs(int now, int prev) {
      level[now] = level[prev] + 1;
      parent[now] = prev;
      for (auto u: adj[now]) {
            if (u != prev) {
                  dfs(u, now);
            }
      }
}

int solve(int x, int lcax, int y, int lcay) {
      int k = lca(x, y);
      if (level[k] <= level[lcax] || level[k] <= level[lcay]) return 0;

      return min(abs(level[k] - level[lcax]), abs(level[k] - level[lcay]));
}

int inPath(int a, int b, int LCAab, int x) {
      int u = lca(a, x);
      int v = lca(b, x);

      if (u == x) {
            if (level[x] <= level[u] && level[x] >= level[LCAab]) return 1;
            else return 0;
      } else if (v == x) {
            if (level[x] <= level[v] && level[x] >= level[LCAab]) return 1;
            else return 0;
      }
      return 0;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> q;
      for (int i = 1; i < n; i++) {
            int x, y; cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
      }
      dfs(1, 0);
      LCAinit();

      while (q--) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            int x = lca(a, b);
            int y = lca(c, d);

            int ans = solve(a, x, c, y) + solve(a, x, d, y) + solve(b, x, c, y) + solve(b, x, d, y) + 1;
            if (ans == 1) {
                  if (inPath(a, b, x, y) || inPath(c, d, y, x)) ans = 1;
                  else ans = 0;
            }
            cout << ans << '\n';
      }

	return 0;
}
