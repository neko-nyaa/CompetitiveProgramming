/*
      https://www.spoj.com/problems/METEORS/

      - LaTeX is not showing correctly on my computer. Because of this, I want to clarify the inputs.
      The query format is [L, R, val], where if L > R then it's [1, R] and [L, M].
      Bounds on N, M, Q is 3e5 and on other values they are 1e9.

      - Very helpful tutorial: http://codeforces.com/blog/entry/45578 . I will try to explain from my understanding.

      - We will apply "parallel binary search". I like to think of it as a mix of binary search and divide and conquer.
      We will group each states, and will apply divide and conquer to answer for all states at once.

      - To query for each state efficiently, we need to do range sum updates and point sum queries.
      In fact we don't even need lazy propagation for this.

      - To add range [l, r] by +val, we will update arr[l] by +val and arr[r+1] by -val.
      To query for sum at point P, we will query for sum in range [1, P]

      - The above technique was also used in CF 383C (Propagating tree): https://codeforces.com/contest/383/problem/C
      On how it was used, please refer to editorial.

      - Apparently this can be solved with persistent segment tree as well.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, q;
vector<ll> tree(1200008);

vector<int> need(300002);
vector<int> property[300002];
vector<tuple<int, int, ll>> que(300002);

vector<int> ans(300001);

void update(int node, int start, int end, int ind, ll val) {
	if (start == end) {
		tree[node] += val;
		return;
	}

	int mid = (start + end) / 2;
      if (start <= ind && ind <= mid) update(node*2, start, mid, ind, val);
	else update(node*2 + 1, mid + 1, end, ind, val);

	tree[node] = tree[2*node] + tree[2*node+1];

}

ll query(int node, int start, int end, int l, int r) {
	if (start > end || start > r || end < l) {return 0;}

	if (start >= l && end <= r) {return tree[node];}

	int mid = (start + end)/2;
	ll p1 = query(node*2, start, mid, l, r);
	ll p2 = query(node*2 + 1, mid+1, end, l, r);
	return p1 + p2;
}

void update(int l, int r, ll val) {
      if (l <= r) {
            update(1, 1, m+1, l, val);
            update(1, 1, m+1, r+1, -val);
      } else if (l > r) {
            update(1, 1, m+1, 1, val);
            update(1, 1, m+1, r+1, -val);
            update(1, 1, m+1, l, val);
            update(1, 1, m+1, m+1, -val);
      }
}

ll query(int ind) {
      return query(1, 1, m+1, 1, ind);
}

void solve(int lo, int hi, vector<int> &v, int &cur) {
      if (v.empty()) return;

      int mid = (lo + hi)/2;

      while (cur < mid) {
            cur++;
            int x, y; ll z;
            tie(x, y, z) = que[cur];
            update(x, y, z);
      }
      while (cur > mid) {
            int x, y; ll z;
            tie(x, y, z) = que[cur];
            update(x, y, -z);
            cur--;
      }

      vector<int> losers, winners;
      for (int u: v) {
            ll met = 0;
            for (int p: property[u]) {
                  met += query(p);
                  if (met >= need[u]) {break;}
            }
            if (met < need[u]) {losers.push_back(u);}
            else {
                  winners.push_back(u);
                  ans[u] = hi;
            }
      }
      v.clear();

      if (lo < hi) {
            solve(lo, mid, winners, cur);
            solve(mid+1, hi, losers, cur);
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> m;
      for (int i = 1; i <= m; i++) {
            int x; cin >> x;
            property[x].push_back(i);
      }
      for (int i = 1; i <= n; i++) {
            cin >> need[i];
      }

      cin >> q;
      for (int i = 1; i <= q; i++) {
            int x, y; ll z; cin >> x >> y >> z;
            que[i] = make_tuple(x, y, z);
      }

      vector<int> v;
      for (int i = 1; i <= n; i++) {
            v.push_back(i);
      }

      int cur = 0;
      solve(1, q, v, cur);

      for (int i = 1; i <= n; i++) {
            if (ans[i]) cout << ans[i] << '\n';
            else cout << "NIE\n";
      }

	return 0;
}
