/*
	This problem at first looks like a super hard and nasty meet-in-the-middle, but it is actually nice and easy.

	- We have at most 2^36 possible grids, we can't iterate through all of them.
	
	- Let's notice, for every possible clues, there can't be too many possible answers.
		+ Clue 1 1 1: There are 4 possible answers.
		+ Clue 1 1: There are 10 possible answers.
	- So we can just generate every possible answers of each row, then try every possible combinations of these answers and check if they satisfy the clues.
*/

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

int r, c;
long long ans = 0;
vector<int> R[6], C[6];
vector<int> masks[6];

int valid(int msk, int len, vector<int> rq) {
	int cur = 0;
	vector<int> gen;
	for (int i = 0; i < len; i++) {
		if (msk & (1 << i)) {
			cur++;
		} else {
			if (cur > 0) gen.push_back(cur);
			cur = 0;
		}
	}
	if (cur > 0) gen.push_back(cur);

	return (rq == gen);
}

void check(vector<int> msk) {
	vector<int> cl(c);
	for (int i = 0; i < r; i++) {
		for (int b = 0; b < c; b++) {
			if (msk[i] & (1 << b)) {
				cl[b] |= (1 << i);
			}
		}
	}
	int mm = 1;
	for (int i = 0; i < c; i++) {
		if (!valid(cl[i], r, C[i])) mm = 0;
	}
	ans += mm;
}

void recur(int i, vector<int> msk) {
	if (i == r) {
		check(msk);
	} else {
		for (int j = 0; j < masks[i].size(); j++) {
			msk.push_back(masks[i][j]);
			recur(i+1, msk);
			msk.pop_back();
		}
	}
}

void solve() {
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			R[i].push_back(x);
		}
	}
	for (int i = 0; i < c; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			C[i].push_back(x);
		}
	}

	// for each row, generate all possible masks of length C
	for (int i = 0; i < r; i++) {
		for (int m = 0; m < (1 << c); m++) {
			if (valid(m, c, R[i])) {
				masks[i].push_back(m);
			}
		}
	}

	// iterate through all possible combination of masks
	recur(0, vector<int>());
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}