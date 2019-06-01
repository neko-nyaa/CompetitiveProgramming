/*
	- Parallel binary search or persistent 2D fenwick? Choose your pokemon

	- For each query, we will binary search on the answer.
	  The answer for a query is the smallest X, such that there are at least K numbers <= X in that range.

	- To query quickly, we can use a persistent 2D fenwick.
	  Simply add every values in the matrix in increasing order.

	- Or we can apply parallel binary search and answer every queries at once.
*/

#include <bits/stdc++.h>
using namespace std;

struct fenwick2d{
	int tree[300][300];

	fenwick2d() {
		memset(tree, 0, sizeof(tree));
	}

	void update(int r, int c, int val = 1) {
		for (int x = r; x < 300; x += x & -x) {
			for (int y = c; y < 300; y += y & -y) {
				tree[x][y] += val;
			}
		}
	}

	int query(int r, int c) {
		int ans = 0;
		for (int x = r; x > 0; x -= x & -x) {
			for (int y = c; y > 0; y -= y & -y) {
				ans += tree[x][y];
			}
		}
		return ans;
	}

	int query(int r1, int c1, int r2, int c2) {
		r1--; c1--;
		int ans = 0;

		ans += query(r1, c1);
		ans += query(r2, c2);
		ans -= query(r1, c2);
		ans -= query(r2, c1);

		return ans;
	}
};

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n; cin >> n;
	vector<tuple<int, int, int>> a;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x; cin >> x;
			a.emplace_back(x, i, j);
		}
	}
	sort(a.begin(), a.end());

	int q; cin >> q;
	vector<tuple<int, int, int, int>> query;
	vector<int> ind(q);
	for (int i = 0; i < q; i++) {
		ind[i] = i;
		int r, c, s, k; cin >> r >> c >> s >> k;
		query.emplace_back(r, c, s, k);
	}

	vector<tuple<int, int, vector<int>>> bfs;
	bfs.push_back(make_tuple(1, 10000, ind));
	
	vector<int> ans(q);
	while (bfs.size()) {
		int ptr = 0;
		fenwick2d fd;
 
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
			while (ptr < n*n && get<0>(a[ptr]) <= mid) {
				int x, i, j; tie(x, i, j) = a[ptr];
				fd.update(i, j);

				ptr++;
			}
 
			if (v.empty()) continue;
 
			vector<int> win, lose;
			for (auto u: v) {
				int r, c, s, k; tie(r, c, s, k) = query[u];

				int r1 = r, r2 = r+s-1;
				int c1 = c, c2 = c+s-1;

				if (fd.query(r1, c1, r2, c2) >= k) {
					win.push_back(u);
				} else {
					lose.push_back(u);
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