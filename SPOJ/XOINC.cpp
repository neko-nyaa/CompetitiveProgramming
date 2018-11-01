/*
      https://www.spoj.com/problems/XOINC/

      - Is this another DP? Yes it is. Let's identify what the states are, such that one can lead to another.

      - What does a move depend on? It depends on how many coins there are left in the stack, and how many coins the opponent took last move.

      - Let's define DP[i][j] as maximum score achievable with i coins left in the stack, and the opponent took j coins last move.
      Our answer will be on DP[n][1], because we have n coins in the stack initially, and we can consider the opponent to have taken 1 coin in the 0-th move.

      - We want to maximize the answer, so the formula will be DP(i, j) = max(c = 1 -> 2*j){sum[1..i] - DP(i - c, c)}
      This gives us O(N^3) solution.

      - To optimize this to O(N^2), notice there are a lot of overlaps between DP(i, j) and DP(i, j+1). We will exploit that to reduce our calculation.

      - Official solution:
      http://contest.usaco.org/TESTDATA/NOV09.xoinc.htm

      - Very nice recursive implementation:
      https://github.com/racsosabe/CompetitiveProgramming/blob/master/SPOJ/XOINC.cpp
*/

#include <bits/stdc++.h>
using namespace std;

int a[5008];
int dp[5008][5008];

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      for (int i = 1; i <= n; i++) {
            cin >> a[i];
      }
      reverse(a+1, a+1+n);
      for (int i = 1; i <= n; i++) {
            a[i] += a[i-1];
      }

      for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                  dp[i][j] = max(dp[i][j], dp[i][j-1]);

                  if (i >= 2*j-1) dp[i][j] = max(dp[i][j], a[i] - dp[i - (2*j-1)][2*j-1]);
                  if (i >= 2*j) dp[i][j] = max(dp[i][j], a[i] - dp[i - (2*j)][2*j]);
            }
      }

      cout << dp[n][1];

      return 0;
}
