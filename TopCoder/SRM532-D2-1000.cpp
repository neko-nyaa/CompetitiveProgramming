/*
	https://community.topcoder.com/stat?c=problem_statement&pm=11765&rd=14725
	- Link might not work, please refer to arena in that case.

	- Tutorial: https://apps.topcoder.com/wiki/display/tc/SRM+532
	Explains really really well. Please read it.

	- My way of understanding is, mask DP, but not bitmask or binary mask, it's ternary mask.

	- For each square, we will keep DP[col][row][profile], with profile being a ternary mask denoting it's "profile".
	When we reach a square, we have two choices: to color it, or not to color it.
		+ If we decide not to color the square, then we just have to transfer the result from the previous state.
		+ If we decide to color the square, we will have to find the new profile, and transfer accordingly.
	- Note that sometimes not both options are available, we can't make our profile invalid.

	- The author's abuses pre-computation a lot. All the numbers done in the pre-calc are just for
	easier working in base-3. I am more comfortable with math, so I make my own functions:
		+ init(): pre-calculates powers of 3
		+ digit(int num, int j): returns the j-digit of num (in base 3)
		+ set(int num, int j, int k): sets the j-digit of num to k (also base 3)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DengklekPaintingSquares{
public:
// 6561 is 3^8

	int pw[10];

	int dp[103][10][6562];		// dp[col][row][profile]
	int M = 1e9+7;

	void init() {
		pw[0] = 1;
		for (int i = 1; i < 10; i++) {
			pw[i] = pw[i-1] * 3;
		}
	}

	int digit(int num, int j) {
		return (num / pw[j]) % 3;
	}

	int set(int num, int j, int k) {
		return num + pw[j]*(k - digit(num, j));
	}

	int valid(int k) {
		for (int i = 0; i < 8; i++) {
			if (digit(k, i) == 1) return 0;
		}
		return 1;
	}

	int numSolutions(int n, int m) {
		init();

		int start = 0;
		for (int j = 0; j < m; j++) {
			start = set(start, j, 2);	// the imaginary row :D
		}
		dp[0][0][start] = 1;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < pw[m]; k++) {

				// don't color it
					if (digit(k, j) != 1) {
						dp[i][j+1][set(k, j, 2)] += dp[i][j][k];
						dp[i][j+1][set(k, j, 2)] %= M;
					}

				// color it
					if (digit(k, j) != 0) {
						int next_k = set(k, j, 0);

						if (digit(k, j) == 1) {
							next_k = set(next_k, j, 1 - digit(next_k, j));
						}

						if (j > 0 && digit(k, j - 1) != 2) {
							next_k = set(next_k, j, 1 - digit(next_k, j));
							next_k = set(next_k, j, 1 - digit(next_k, j - 1));
						}

						dp[i][j+1][next_k] += dp[i][j][k];
						dp[i][j+1][next_k] %= M;
					}

				}
			}

			for (int k = 0; k < pw[m]; k++) {
				dp[i+1][0][k] = dp[i][m][k];
			}
		}

		int ans = 0;
		for (int k = 0; k < pw[m]; k++) {
			if (valid(k)) {
				ans = (ans + dp[n][0][k]) % M;
			}
		}
		return ans;
	}
};
