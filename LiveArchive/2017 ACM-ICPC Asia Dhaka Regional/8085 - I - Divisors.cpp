/*
	The overflow is super scary, I wonder how did they do this problem

	- This is called superfactorials, but it's actually not important.

	- In the normal "find divisors of factorials", we find the power of each prime divisor.
	- We apply the same idea here.

	Also, this code doesn't work on Windows machines
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> p;

void init() {
	vector<bool> s(5000001);
	for (int i = 2; i <= 5000000; i++) {
		if (!s[i]) {
			p.push_back(i);
			for (long long j = 1LL*i*i; j <= 5000000; j += i) {
				s[j] = 1;
			}
		}
	}
}

const long long M = 1e8 + 7;

__int128 f(int n) {
	return 1LL*n*(n+1)/2;
}

__int128 countdiv(int d, int n) {
	__int128 ans = 0;
	for (long long i = d; i <= n; i = i*d) {
		__int128 p = f(n) - (n/i)*f(i - 1) - f(n % i);
		ans += p/i;
	}
	return ans;
}

void solve(int n) {
	__int128 ans = 1;
	for (int i: p) {
		if (i > n) break;
		ans = (ans * (countdiv(i, n) + 1)) % M;
	}
	cout << (long long)ans << '\n';
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