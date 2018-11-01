/*
	http://community.topcoder.com/stat?c=problem_statement&pm=15142&rd=17316

	- Given a 47-digit number S and a number X not exceeding 777,444,111, count how many subsequences of S are there,
	such that the number created from the subsequence is GREATER than X, and have no leading zeros.

	- Our numbers S and X have 47 and 9 digits respectively. We have C(47, 9) is over 1 billion, we can't afford to check everything.
	Time to do dynamic programming? Let's go.

      - Let's think about how we can construct a number from S. Let's iterate through it's digits. When we arrive at the i-th digit, we have two choices:
            + Take that digit, add it to our number, move on.
            + Ignore that digit, do nothing, and move on.
      - Be careful of leading zeroes. We can't take our first number as 0, so there are cases we can't use the first choice.

      - What makes a constructed number acceptable? Either one of these conditions must hold:
            + The number we have picked have more digits than X.
            + The number we have picked have equal digits as X, and some prefix of the number is strictly larger.

      - Now we know all the conditions we have to put together, we can construct the DP table.
      Let DP[i][j][flag] denote:
            + i: We have arrived at the i-th digit, and now considering if we take it or not.
            + j: We have taken j digits so far.
            + flag: Can have values 0/1/2, denoting:
                  0: The number constructed so far is smaller than the j-prefix of X
                  1: The number constructed so far is equal to the j-prefix of X
                  0: The number constructed so far is greater than the j-prefix of X
      - Editorial explains this part really well, please read it. Link at the end of code header.

      - What will the transition be? When we arrive at DP[i][j][flag], we have a few cases:
            + flag is equal to 1. That means the next flag can be 1, 2, or 0, depending on our choice of taking this number or not.
            + flag is equal to 0 or 2. That means our number's prefix is already not equal to X's prefix. Therefore flag cannot change regardless of our choice.
      - To sum up: DP[i][j][flag] = DP[i+1][j][flag] + DP[i+1][j+1][new_flag]

      - Base case: i = n (processed everything, yay), DP[i][j][flag] = 1 or 0 depending on our constructed number is acceptable or not.

      - This implementation uses recursive approach. I find it more straight-forward and understandable.

	- Editorial: https://www.topcoder.com/blog/single-round-match-741-editorials/
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DigitStringDiv1{
public:
	long long dp[50][50][3];
	int n, m;
	string s;
	string x;

	// 0 is to less
	// 1 is to equal
	// 2 is to more

	long long solve(int i, int j, int flag) {
		if (j > m) flag = 2;
		if (i == n) return (j >= m && flag == 2);

		if (dp[i][j][flag] != -1) return dp[i][j][flag];

		if (s[i] == '0' && j == 0) {
			return dp[i][j][flag] = solve(i+1, j, flag);
		}

		if (flag == 1) {
			long long ans = 0;
			if (s[i] == x[j]) ans += solve(i+1, j+1, 1);
			else if (s[i] > x[j]) ans += solve(i+1, j+1, 2);
			else ans += solve(i+1, j+1, 0);

			ans += solve(i+1, j, flag);

			return dp[i][j][flag] = ans;

		} else {
			long long ans = 0;
			ans += solve(i+1, j+1, flag);
			ans += solve(i+1, j, flag);

			return dp[i][j][flag] = ans;
		}
	}

	long long solve() {
		memset(dp, -1, sizeof(dp));
		return solve(0, 0, 1);
	}

	long long count(string S, int X) {
		if (S == "0") return 0;

		s = S;
		x = to_string(X);
		n = s.size(); m = x.size();

		return solve();
	}
};
