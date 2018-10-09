/*
      https://agc002.contest.atcoder.jp/tasks/agc002_d

      - Let's think of how to solve an individual query first. The brothers can reach a score of i if, we add all edges of indices below i,
      and the brothers can reach at least z vertices. It's clear we will need a DSU.

      - Now we have a lot of queries. Clearly we can't answer each one individually. Instead we will apply "parallel binary search"
      and answer all these queries at once.

      - A helpful tutorial on this technique: https://codeforces.com/blog/entry/45578

      - We can imagine this search technique as a binary tree. To avoid initializing the DSU way too many times, we will descend the tree with BFS.
      This way, we will need to initialize DSU only once per level of the tree.

      - This gives us complexity of O((Q+M)*logM), plus some inverse ackermann factor.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct DSU {
	vector<int> P, S;
	DSU(int n) {
		P.resize(n+1);
		S.resize(n+1, 1);
		for (int i = 1; i <= n; i++) P[i] = i;
	}

	int find(int x) {
		while (x != P[x]) x = P[x];
		return x;
	}

	int sz(int x) {
		return S[find(x)];
	}

	void merge(int a, int b) {
		a = find(a); b = find(b);
		if (S[a] < S[b]) swap(a, b);

		S[a] += S[b];
		P[b] = a;
	}

	int same(int a, int b) {
		return find(a) == find(b);
	}
};

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n, m, q; cin >> n >> m;
      vector<int> a(m+1), b(m+1);
      for (int i = 1; i <= m; i++) {
            cin >> a[i] >> b[i];
      }
      cin >> q;
      vector<int> x(q), y(q), z(q), ans(q, 0);
      for (int i = 0; i < q; i++) {
            cin >> x[i] >> y[i] >> z[i];
      }

      vector<int> ind;
      for (int i = 0; i < q; i++) {
            ind.push_back(i);
      }

      vector<tuple<int, int, vector<int>>> bfs;
      bfs.push_back(make_tuple(1, m, ind));

      while (bfs.size()) {
            DSU d(n);
            int e = 0;

            vector<tuple<int, int, vector<int>>> next;
            sort(bfs.begin(), bfs.end());

            for (auto temp: bfs) {
                  int lo, hi; vector<int> v;
                  tie(lo, hi, v) = temp;

                  if (lo == hi) {
                        for (int u: v) ans[u] = lo;
                        continue;
                  }

                  int mid = (lo + hi)/2;
                  while (e < mid) {
                        e++;
                        if (!d.same(a[e], b[e])) {
                              d.merge(a[e], b[e]);
                        }
                  }

                  if (v.empty()) continue;

                  vector<int> win, lose;
                  for (auto u: v) {
                        if (d.same(x[u], y[u])) {
                              if (d.sz(x[u]) >= z[u]) {
                                    win.push_back(u);
                                    ans[u] = hi;
                              } else {
                                    lose.push_back(u);
                              }
                        } else {
                              if (d.sz(x[u]) + d.sz(y[u]) >= z[u]) {
                                    win.push_back(u);
                                    ans[u] = hi;
                              } else {
                                    lose.push_back(u);
                              }
                        }
                  }

                  if (lo < hi) {
                        next.push_back(make_tuple(lo, mid, win));
                        next.push_back(make_tuple(mid+1, hi, lose));
                  }
            }

            swap(bfs, next);
      }

      for (int i: ans) cout << i << '\n';

	return 0;
}
