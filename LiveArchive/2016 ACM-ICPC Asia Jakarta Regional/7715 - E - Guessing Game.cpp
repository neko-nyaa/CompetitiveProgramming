/*
	- This is a classic stars-and-bars + inclusion-exclusion problem.

	- Suppose we have binomial coefficient C(N, K), we can calculate it in O(K).
	  Here K is just 3

	- To find the answer modulo M for a prime M, we apply Lucas' theorem.
*/

#include <bits/stdc++.h>
using namespace std;

const long long M = 1e9+7;
long long modpow(long long n, long long k, long long MOD);

long long nC2(long long n) {
	if (n < 2) return 0;

	n %= M;
	return (n*(n-1)/2) % M;
}

void solve() {
	vector<long long> l(3), r(3);
	long long n;

	for (int i = 0; i < 3; i++) {
		cin >> l[i] >> r[i];
	}
	cin >> n;

	for (int i = 0; i < 3; i++) {
		n -= l[i];
		r[i] -= l[i];
	}

	// okay let's solve lol
	long long ans = 0;

	for (int mask = 0; mask < 8; mask++) {
		long long p = 0;
		for (int i = 0; i < 3; i++) {
			if (mask & (1 << i)) {
				p += r[i]+1;
			}
		}

		long long sum = nC2(n - p + 2); // is actually n-p+3-1

		if (__builtin_popcount(mask) % 2) ans -= sum;
		else ans += sum;

		ans %= M;
	}

	cout << (ans + M) % M << '\n';
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