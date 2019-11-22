#include <bits/stdc++.h>
using namespace std;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> b = a;
	sort(b.begin(), b.end());

	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		if (b[i] != a[i]) {
			// find last occurrence of b[i]
			l = i;
			for (int j = i; j < n; j++) {
				if (b[i] == a[j]) {
					r = j;
				}
			}
			reverse(a.begin()+l, a.begin()+r+1);
			break;
		}
	}

	if (a == b) cout << l+1 << ' ' << r+1;
	else cout << "impossible";

 
	return 0;
}