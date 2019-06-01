/*
	- Finite geometric series
*/

#include <bits/stdc++.h>
using namespace std;

const long long M = 1000000007;
long long modpow(long long n, long long k, long long MOD);

long long f(long long a, long long b) {
	if (a == 1) return b+1;
	if (b == -1) return 0;

	long long p = (1 - modpow(a, b+1, M) + M) % M;
	long long q = (1 - a + M) % M;

	return (p * modpow(q, M-2, M)) % M;
}

void solve() {
	int n; cin >> n;
	long long ans = 1;

	while (n--) {
		long long a, b, c; 
		cin >> a >> b >> c;
		ans = (ans * (f(a, c) - f(a, b-1) + M)) % M;
	}
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
	
	return 0;
}

long long modpow(long long n, long long k, long long MOD) {
	long long ans = 1; n %= MOD;
	while (k > 0) {
		if (k & 1) ans = (ans*n) % MOD;
		k >>= 1; n = (n*n) % MOD;
	}
	return ans; 
}