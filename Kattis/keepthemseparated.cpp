/*
	https://open.kattis.com/problems/keepthemseparated

	- The problem is identical to https://codeforces.com/contest/869/problem/E
	Tutorial here: https://codeforces.com/blog/entry/55009

	- Let's understand the problem as follow: for each update operation, we will add a rectangle into our field.
	From the non-overlapping constrain of rectangles, two cells are reachable if both these cells have the same set of rectangles which they stand on.

	- We can uniquely (or almost uniquely) define a rectangle using hashing. For each rectangle, we will assign a random integer value. 
	Suppose we want to add/delete a rectangle, we will need to update the field with that rectangle.

	- We have almost arrived at the solution. We will need to support these two operations:
		+ Range update: updating a rectangular range with a hash value.
		+ Point query: returns the hash value of a point.
	- This can be easily done with a 2D fenwick. We will update in a prefix-sum manner, so we won't need lazy propagation:
		+ For updates, we will update the four corners with the hash value. 
		+ For query, we will query the prefix sum of the point.
	- Reversible operations such as xor or plus/minus will work well on this problem.

	- To check if two cells are reachable, just check if their hash values are the same.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int q;
int tree[5003][5003];
vector<tuple<int, int, int, int, int>> que(100005);

void update(int r, int c, int val) {
	for (int x = r; x < 5003; x += x & -x) {
		for (int y = c; y < 5003; y += y & -y) {
			tree[x][y] += val;
		}
	}
}

void update(int r1, int c1, int r2, int c2, int val) {
	r2++; c2++;
	update(r1, c1, val);
	update(r2, c2, val);
	update(r1, c2, -val);
	update(r2, c1, -val);
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

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> q;
	for (int i = 1; i <= q; i++) {
		int t; cin >> t;

		if (t == 1) {
			int r1, c1, r2, c2, val;
			cin >> r1 >> c1 >> r2 >> c2;

			val = rng();
			que[i] = make_tuple(r1, c1, r2, c2, val);
			update(r1, c1, r2, c2, val);
		} else if (t == 2) {
			int r1, c1, r2, c2, val;
			int j; cin >> j;
			tie(r1, c1, r2, c2, val) = que[j];

			update(r1, c1, r2, c2, -val);
		} else if (t == 3) {
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;

			if (query(r1, c1) == query(r2, c2)) {
				cout << "Y";
			} else {
				cout << "N";
			}
		}
	}

	return 0;
}
