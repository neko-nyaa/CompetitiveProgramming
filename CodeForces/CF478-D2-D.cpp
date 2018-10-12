/*
      https://codeforces.com/contest/478/problem/D

      - Let's assume r >= g. We will do dp[h][r], where h is our required tower height.

      - We can decide to color the i-th level red or green. We will denote dp[i][j], how many ways can be build up to the i-th level,
      using at most j red blocks, suppose we have infinite green blocks. The answer is the sum of all dp[h][j].

      - In order to put a constrain to the green blocks, we will only add to the answer dp[h][j] such that j >= (total block) - g.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int r, g, h, M = 1e9+7;
      cin >> r >> g;
      if (r < g) swap(r, g);

      for (h = 1000; h*(h+1)/2 > r+g; h--);

      vector<int> dp(r+1, 0);
      dp[0] = dp[1] = 1;

      for (int i = 1; i < h; i++) {
            vector<int> tmp = dp;

            for (int j = i+1; j <= r; j++) {
                  tmp[j] = (tmp[j] + dp[j - i - 1]) % M;
            }

            swap(dp, tmp);
      }

      int ans = 0;
      for (int i = max(0, h*(h+1)/2 - g); i <= r; i++) {
            ans = (ans + dp[i]) % M;
      }
      cout << ans;

      return 0;
}
