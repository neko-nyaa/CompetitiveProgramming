/*
      https://codeforces.com/contest/1073/problem/E

      - In this problem, we have to find sum of all numbers between L and R inclusive, such that their distinct digit count is no more than K.

      - It's easy to see ans(L, R) = ans(1, R) - ans(1, L-1). We will solve these 2 problems on the right side.
      Sounds like digit DP? Yes it is.

      - Let's think about how we can construct a valid number digit-by-digit. We will need the following information:
                  + Whether the number constructed so far is still equal to the prefix of N, or is it guaranteed to be less than N at this point.
                  + What digits have we used so far.

      - The first info can be obtained with a boolean. This is a classic trick in digit DP.
      - The second info can be obtained with a bitmask. We will represent this with a number, the i-th bit set to 1 if digit i was already used.

      - Now we can use bitmask and digit DP to solve this problem (two named DP techniques at once!!!!!). We will need two tables:
                  DP[i][j][mask] to count ways to construct the i-th digit, with the respective mask. The transition is similar to normal digit DP.
                  ANS[i][j][mask] storing the sum of numbers constructed so far. The transition is, we will shift the previous number by one place and add our new digit.
      - See implementation for clearer idea of transition. Of course it can be merged into one 4D table as well.

      - The answer is the sum of all DP[N][j][mask], such that number of 1-bit in mask is not more than K.
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
int M = 998244353;

int dp[20][2][1080];
int ans[20][2][1080];

int solve(int n, int k) {
      string s = to_string(n);
      memset(dp, 0, sizeof(dp));
      memset(ans, 0, sizeof(ans));
      n = s.size();

      dp[0][1][0] = 1;
      for (int i = 0; i < n; i++) {
            for (int j = 0; j < 1024; j++) {
                  for (int less = 0; less < 2; less++) {
                        for (int dig = 0; dig < 10; dig++) {
                              if (less && (dig > s[i] - '0')) continue;

                              int mask = (j == 1 ? 0 : j) | (1 << dig);
                              int ls = (dig == s[i] - '0') & less;

                              dp[i+1][ls][mask] = (dp[i+1][ls][mask] + dp[i][less][j]) % M;
                              ans[i+1][ls][mask] = (ans[i+1][ls][mask] + 10*ans[i][less][j] + dig*dp[i][less][j]) % M;
                        }
                  }
            }
      }

      int res = 0;
      for (int i = 0; i < 1024; i++) {
            if (__builtin_popcountll(i) <= k) {
                  res = (res + ans[n][0][i]) % M;
                  res = (res + ans[n][1][i]) % M;
            }
      }
      return res;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int l, r, k;
      cin >> l >> r >> k;
      int ans = (solve(r, k) - solve(l-1, k)) % M;
      if (ans < 0) ans += M;
      cout << ans;

      return 0;
}
