#include <bits/stdc++.h>
using namespace std;

const long long M = 1e9+7;
long long ft[1000001];
long long modpow(long long n, long long k, long long MOD);
 
void init() {
	ft[0] = ft[1] = 1;
	for (int i = 2; i <= 1000000; i++) {
		ft[i] = (ft[i-1] * i) % M;
	}
}
 
long long nCr(long long n, long long r) {
	long long p = ft[n];
	long long q = (ft[r]*ft[n-r]) % M;
	return p*modpow(q, M-2, M) % M;
}

int n, m;

void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int k, x; cin >> k;
		while (k--) cin >> x;
	}
}

void solve() {
	if (m < n) cout << "0\n";
	else cout << nCr(m-1, n-1) << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();

	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		input(); solve();
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