/*
	- https://codeforces.com/contest/1042/problem/E

	- This problem is actually really easy once we lay everything out, and plan carefully.
	- The expected score of a certain starting square depends on expected score of squares it can move to.
	- So we can sort the squares by value, and process them in increasing order.
	- The plan is to write down the formula, then notice how we can transform the formula into something efficient.
	- By linearty of expectation, the EV of a square is equal to EV of every squares it can move to, plus the score of the move itself.
	- If we can write down this formula and implement it, we can solve this problem in O(square^2)
	- If we process the squares in increasing order, then we can maintain an accumulative sum of several parts of the formula, allowing O(square) solution.

	- If it's still unclear, the formula itself is in the editorial:
		https://codeforces.com/blog/entry/61891
	  The editorial explains very clearly.
*/

#include <bits/stdc++.h>
using namespace std;

const long long M = 998244353;
long long modpow(long long n, long long k, long long MOD);

int n, m;
vector<tuple<int, int, int>> positions;
long long ev[1002][1002];
long long RR, R, CC, C, evsum, k;

void process(vector<pair<int, int>> &coor) {
	long long invk = modpow(k, M-2, M);
	for (auto [r, c]: coor) {
		ev[r][c] = (evsum + r*r*k + c*c*k - 2*r*R - 2*c*C + CC + RR) % M;
		ev[r][c] = (ev[r][c] * invk) % M; 
	}

	for (auto [r, c]: coor) {
		CC = CC + c*c;
		RR = RR + r*r;
		C = C + c;
		R = R + r;
		evsum = evsum + ev[r][c];
		k++;
	}

	coor.clear();
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int v; cin >> v;
			positions.emplace_back(v, i, j);
		}
	}
	sort(positions.begin(), positions.end());

	vector<pair<int, int>> coor;
	for (int i = 0; i < n*m; i++) {
		coor.emplace_back(get<1>(positions[i]), get<2>(positions[i]));
		
		if (i == n*m - 1 || get<0>(positions[i]) != get<0>(positions[i+1])) {
			process(coor);
		}
	}
	
	int x, y; cin >> x >> y;
	cout << ev[x][y] << '\n';
	
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