#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node{
	int cc, l, r;
};

int n, m, q;
int a[10][100001];
vector<node> tree(400005);

node operator + (const node& l, const node &r) {
      node ans;

      if (l.cc == -1) return r;
      if (r.cc == -1) return l;

	ans.cc = l.cc + r.cc;
      ans.l = l.l; ans.r = r.r;
      int left = l.r, right = r.l;
      for (int i = 0; i < n; i++) {
            if (a[i][left] == a[i][right]) ans.cc--;
      }

	return ans;
}

void build(int p, int start, int end) {
	if (start == end) {
            tree[p].cc = n;
            tree[p].l = tree[p].r = start;

            for (int i = 1; i < n; i++) {
                  if (a[i][start] == a[i-1][start]) tree[p].cc--;
            }
	} else {
		int mid = (start + end)/2;

		build(p*2, start, mid);
		build(p*2+1, mid+1, end);

		tree[p] = tree[2*p] + tree[2*p + 1];
	}
}

node query(int p, int start, int end, int l, int r) {
	if (l > end || r < start) return {-1, -1, -1};
	if (l <= start && end <= r) return tree[p];

	int mid = (start + end)/2;

	return query(2*p, start, mid, l, r) + query(2*p + 1, mid+1, end, l, r);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                  cin >> a[i][j];
            }
	}
	build(1, 1, m);

      while (q--) {
            int l, r; cin >> l >> r;
            node ans = query(1, 1, m, l, r);
            cout << ans.cc << '\n';
      }

	return 0;
}
