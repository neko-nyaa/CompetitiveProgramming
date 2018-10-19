/*
      https://csacademy.com/contest/round-40/task/restricted-permutations/statement/

      - Let's think about how we can construct a valid permutation. Let's start with an empty permutation P = {}

      - We will insert numbers one by one, in order. Here I will insert from largest to smallest.

      - How to insert number i? Note that if our permutation currently has |P| elements, then there are a total of |P+1| positions to insert number in.
      Now our question becomes, how many ways can we insert all N numbers in, such that all conditions are satisfied.

      - Let's build a table dp[][], where dp[i][j] is the number of ways to insert the number i into position j.
      We will work with i from N down to 1. Our DP table will look like a pyramid.

      - Here's the DP table for sample test 2:
            1
            1 0
            0 1 1
            2 2 1 0
            5 3 1 0 0
      - We can see there are 9 ways to insert the number 1 into the permutation.

      - The transition at this point should be clear. dp[i][j] = sum(dp[i+1][k]) for k smaller or larger than (or equal to) j, depending on condition.

      - How to calculate sum(dp[i+1][k]) quickly a lot of times? This is easy, let's do prefix sum :D
*/

#include <bits/stdc++.h>
using namespace std;

int M = 1e9+7;

int n;
int dp[2008][2008];
int a[2008];

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
            scanf("%d", &a[i]);
	}

	dp[n][1] = 1;

      for (int i = n-1, k = 2; i; i--, k++) {
            for (int j = 1; j <= k; j++) {
                  dp[i+1][j] = (dp[i+1][j-1] + dp[i+1][j]) % M;
            }

            for (int j = 1; j <= k; j++) {
                  if (a[i]) {
                        dp[i][j] = (dp[i+1][k] - dp[i+1][j-1]) % M;
                        if (dp[i][j] < 0) dp[i][j] += M;
                  } else{
                        dp[i][j] = dp[i+1][j-1];
                  }
            }
      }

      int ans = 0;
      for (int i = 1; i <= n; i++) {
            ans = (ans + dp[1][i]) % M;
      }
      cout << ans;
}
