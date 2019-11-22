#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

double f(int n, int x, int k) {
	// find (n-x)C(k-2) / nCk
	vector<double> num, denom;
	// 1/nCk = k!*(n-k)!/n!
	for (int i = 1; i <= k; i++) {
		num.push_back(i);
	} 
	for (int i = 1; i <= n-k; i++) {
		num.push_back(i);
	} 
	for (int i = 1; i <= n; i++) {
		denom.push_back(i);
	}

	// (n-x)C(k-2) = (n-x)! / (k-2)!*(n-x-k+2)!
	for (int i = 1; i <= n-x; i++) {
		num.push_back(i);
	} 
	for (int i = 1; i <= k-2; i++) {
		denom.push_back(i);
	} 
	for (int i = 1; i <= n-x-k+2; i++) {
		denom.push_back(i);
	}

	while (num.size() < denom.size()) {
		num.push_back(1);
	}
	while (num.size() > denom.size()) {
		denom.push_back(1);
	}

	double f = 1;
	for (int i = 0; i < num.size(); i++) {
		f *= num[i]/denom[i];
	}
	return f;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 	cout << fixed << setprecision(9);

	int n, k; cin >> n >> k;
	vector<double> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (k == 1) {
		for (int i = 0; i < n; i++) {
			cout << 100.0/n << ' ';
		}
		exit(0);
	} 
	if (k == n) {
		for (int i = 0; i < n; i++) {
			cout << a[i] << ' ';
		}
		exit(0);
	}

	for (int i = 0; i < n; i++) {
		double ans = 0;
		// chances for this one
		double chance = 0;
		for (int j = i, taken = 2; n - taken >= k - 2; taken++) {
			chance += a[j];
			ans += chance*f(n, taken, k);
			j--; if (j < 0) j += n;
		}
		cout << ans << ' ';
	}

	return 0;
}