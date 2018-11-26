/*
      https://codeforces.com/contest/1056/problem/D

      - Editorial: https://codeforces.com/blog/entry/63461

      - The key observation here is, if a vertex is "happy", then all vertices in its subtree are happy.
      A vertex is happy if all it's leaf has distinct colors.

      - So the answer is simply "number of leaves in each vertex", sorted ascending.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
vector<int> adj[100006];
vector<int> lf(100006, 1);

void dfs(int now, int prev) {
      for (auto u: adj[now]) {
            if (u != prev) {
                  dfs(u, now);
                  lf[now] += lf[u];
            }
      }
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      cin >> n;
      for (int i = 2; i <= n; i++) {
            int x; cin >> x;
            adj[x].push_back(i);
            lf[x] = 0;
      }
      dfs(1, 0);
      sort(lf.begin()+1, lf.begin()+1+n);
      for (int i = 1; i <= n; i++) cout << lf[i] << ' ';

	return 0;
}


