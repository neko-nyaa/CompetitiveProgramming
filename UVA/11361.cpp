/*
      https://vjudge.net/problem/UVA-11361

      - It's very important to notice at first, that the constrain for K is abnormally high.
      That's because our number has only 10 digits, and thus its digit sum can be at maximum 82.

      - Now our K is small enough to be iterated through. Let's iterate through multiples of K, and call it S. The question we will be answering now is:
      "How many numbers between A and B are there, such that its digit sum is S, and it is divisible by K."

      - We can do it by digit DP. There is a very helpful tutorial on this:
      https://www.geeksforgeeks.org/count-numbers-smaller-than-or-equal-to-n-with-given-digit-sum/

      - We can modify it to our problem by adding their modulo as a parameter to our DP.
*/

#include <bits/stdc++.h>
using namespace std;

int dp[10][2][83][83];

int solve(int i, int less, int sum, int digitsum, string &s, int n, int div, int mod) {
      if (i == n) {
            return (digitsum == sum && mod == 0);
      }

      if (dp[i][less][sum][mod] != -1) return dp[i][less][sum][mod];

      int ans = 0;

      for (char c = '0'; c <= '9'; c++) {
            if (!less && c > s[i]) break;

            int ls = less || (c < s[i]);
            int sm = sum + (c - '0');

            ans += solve(i+1, ls, sm, digitsum, s, n, div, (mod*10 + c - '0') % div);
      }

      return dp[i][less][sum][mod] = ans;
}

int solve(int n, int digitsum, int div) {
      string s = to_string(n);
      memset(dp, -1, sizeof(dp));

      return solve(0, 0, 0, digitsum, s, s.size(), div, 0);
}

signed main() {
      int t; scanf("%d", &t);
      while (t--) {
            int a, b, k;
            scanf("%d %d %d", &a, &b, &k);
            if (k > 82) {printf("0\n"); continue;}

            int ans = 0;
            for (int i = k; i <= 82; i += k) {
                  ans += solve(b, i, k) - solve(a-1, i, k);
            }
            printf("%d\n", ans);
      }
}
