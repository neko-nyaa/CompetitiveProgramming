/*
	This one is fun
*/

#include <bits/stdc++.h>
using namespace std;

long long modpow(long long n, long long k, long long MOD);
const long long M = 100000007;
long long p2[10000001];

void init() {
	p2[0] = 1;
	for (int i = 1; i <= 10000000; i++) {
		p2[i] = (p2[i-1]*2) % M;
	}
}

void solve(int n) {
	if (n == 1) cout << "1\n";
	else if (n == 2) cout << "18\n";
	else if (n == 3) cout << "132\n";
	else {
		long long ans = p2[n - 4] * (modpow(n, 4, M) + 6*modpow(n, 3, M) + 3*modpow(n, 2, M) - 2*n) % M;
		if (ans < 0) ans += M;
		cout << ans<< '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();

	int n;
	while (cin >> n, n) {
		solve(n);
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