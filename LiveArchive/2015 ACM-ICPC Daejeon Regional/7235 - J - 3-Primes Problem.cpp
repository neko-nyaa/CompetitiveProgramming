#include <bits/stdc++.h>
using namespace std;

vector<int> pr;
vector<tuple<int, int, int>> ans(3001);

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	for (int i = 2; i <= 1000; i++) {
		pr.push_back(i);
		for (int j = 2; j*j <= i; j++) {
			if (i % j == 0) {
				pr.pop_back();
				break;
			}
		}
	}

	for (int i: pr) {
		for (int j: pr) {
			for (int k: pr) {
				if (j >= i && k >= j) {
					ans[i+j+k] = make_tuple(i, j, k);
				}
			}
		}
	}

	int t; cin >> t;
	while (t--) {
		int x; cin >> x;
		int a, b, c; tie(a, b, c) = ans[x];
		cout << a << ' ' << b << ' ' << c << endl;
	}

	return 0;
}