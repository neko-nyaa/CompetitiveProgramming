/*
      http://lightoj.com/volume_showproblem.php?problem=1126
      https://vjudge.net/problem/LightOJ-1126                     Because I can't confirm my lightOJ email.

      - In this problem, we have to find two disjoint subsets, such that their sum is equal, and is the maximum possible.

      - What does "their sum is equal" mean? It means their absolute difference is zero. This is a big step towards the solution

      - Let's try to consider the bricks one by one. When we arrive at the i-th brick, we have several choices:
            + Ignore the brick, move on to the next one
            + Take the brick, put it into the currently-greater set. Their difference now increases.
            + Take the brick, put it into the currently-smaller set. Their difference now decreases (it might flip its sign).
      - Define dp[i][j] as the maximum sum we can obtain with absolute difference j, if we consider the first i bricks, and is -1 if difference j is unreachable.
        Now this becomes a knapsack problem, we can build up the DP table row by row, from 1 to n.

      - But if we define dp[50][500000], we will get memory limit exceeded. How can we optimize that?

      - This is a clear case of state reduction. If we build the table up iteratively, notice how we can build the entire row of dp[i] just from dp[i-1].
      - So actually, this is enough. When we want to build dp[i], we only need dp[i-1]. So we only need to store dp[i] and dp[i-1],
      and delete/ignore everything else once we're done working. This is space reduction, we only store what we absolutely need.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve(int testcase) {
      int dp[2][500001];
      memset(dp, -1, sizeof(dp));
      dp[1][0] = 0;

      int n; scanf("%d", &n);
      int sum = 0;
      while (n--) {
            for (int i = 0; i <= sum; i++) {
                  dp[0][i] = dp[1][i];
            }

            int x; scanf("%d", &x);
            for (int i = 0; i <= sum; i++) {
                  if (dp[0][i] != -1) {
                        // not taking anything
                        dp[1][i] = max(dp[1][i], dp[0][i]);

                        // taking forward
                        int forw = i + x;
                        dp[1][forw] = max(dp[1][forw], dp[0][i] + x);

                        // taking backwards
                        int backw = abs(i - x);
                        dp[1][backw] = max(dp[1][backw], dp[0][i] + x);
                  }
            }
            sum += x;
      }

      int ans = dp[1][0];
      if (ans > 0) {
            printf("Case %d: %d\n", testcase, ans/2);
      } else {
            printf("Case %d: impossible\n", testcase);
      }
}

int main() {
      int t; scanf("%d", &t);
      for (int i = 1; i <= t; i++) {
            solve(i);
      }
}
