/*
	https://cses.fi/problemset/task/1112/

	- Let the input string be S, of length m.

	- The constrain hints towards a dynamic programming solution. We will use just that to solve this problem.
	Let's define dp(i, j, contain) as the number of strings satisfying:
		+ Length i
		+ The j-suffix of this string matches the j-prefix of string S, and j is the longest possible
		+ contain is a boolean being has string S ever appeared in this string before.
	We obtain a simple DP solution by trying every possible characters into position i. 

	- The hard part is the transition of parameter j. 
	If we choose character i such that it matches S[j], we can just increase j by one. 
	But what happens if character i does not match S[j]? Where will j go next? Reset to 0?

	- No, j can't just go straight to 0. Consider S = "ABCAC".
	Suppose we have constructed "ABCA", and we try to set the 5th character be 'B'
	Then by its definition j will move to 2, not 0. So how do we find out where j should move?

	- We will make use of prefix function (pi for short) for this.
	Let's define pi(int i, char c) being the value of the pi-function of S, suppose we change the i-th character to c.
	By its online nature, we can construct pi(i, c) sequentially from (0, 'A') to (m, 'Z') very efficiently.

	- Now we have the transition of parameter j. 
	If S[j] does not match, we just have to move j to pi(j, c), and do our DP normally.
*/

#include <bits/stdc++.h>
using namespace std;
 
const int M = 1000000007;
 
int n, m;
string s, t;
int pi[1024][256];
int nxt[1024][256];
int dp[1024][128][2];
 
void init() {
	vector<int> pref(m); t.push_back(s[0]);
	for (int i = 1; i <= m; i++) {
		for (char c = 'A'; c <= 'Z'; c++) {
			t.push_back(c);
 
			int j = pref[i-1];
			while (j > 0 && t[i] != t[j]) j = pref[j-1];
			if (t[i] == t[j]) j++;
			pref[i] = pi[i][c] = j;
 
			t.pop_back();
		}
 
		if (i == m) break;
		t.push_back(s[i]);
 
		pref[i] = pi[i][s[i]];
	}
 
	for (int i = 0; i <= m; i++) {
		for (char c = 'A'; c <= 'Z'; c++) {
			if (i < m && s[i] == c) nxt[i][c] = i+1;
			else nxt[i][c] = pi[i][c];
		}
	}
}
 
int solve(int i, int j, int contain) {
	if (j == m) contain = 1;
	if (i == n) return contain;

	if (dp[i][j][contain] != -1) return dp[i][j][contain];
 
	int ans = 0;
	for (char c = 'A'; c <= 'Z'; c++) {
		ans = (ans + solve(i+1, nxt[j][c], contain)) % M;
	}
	return dp[i][j][contain] = ans;
}
 
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	cin >> n >> s; m = s.size();
	init();
	memset(dp, -1, sizeof(dp));
 
	int ans = 0;
	cout << solve(0, 0, 0);
 
	return 0;
}