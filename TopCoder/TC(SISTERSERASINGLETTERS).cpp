/*
	https://community.topcoder.com/stat?c=problem_statement&pm=11504&rd=14569
	Editorial: https://apps.topcoder.com/wiki/display/tc/TCO'11+Online+Round+5

	- This solution is an optimized version of editorial solution. 
	- Instead of saving the entire string, we will store two pointers i, pref.
	dp(i, pref, turn) denoting the winning player, suppose the last not-erased character is word[i],
	and the character we are considering is word[i].
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class SistersErasingLetters{
public:
	int n;
	string s;
	int dp[52][52][2];

	int solve(int i, int pref, int turn) {
		if (i == n) {
			return turn;
		}

		if (dp[i][pref][turn] != -1) return dp[i][pref][turn];

		int ans = 0;
		if (!solve(i + 1, pref, 1 - turn)) {
			ans = 1;
		} else if (i < n-1) {
			if (s[i] < s[pref]) {
				ans = turn;
			} else if (s[i] > s[pref]) {
				ans = !turn;
			} else {
				ans = solve(i + 1, pref + 1, turn);
			}
		}

		return dp[i][pref][turn] = ans;
	}

	string whoWins(string word) {
		memset(dp, -1, sizeof(dp));
		s = word; n = s.size();

		return solve(0, 0, 0) ? "Camomile" : "Romashka";
	}
};