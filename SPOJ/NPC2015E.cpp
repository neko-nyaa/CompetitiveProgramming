/*
      https://www.spoj.com/problems/NPC2015E/

      - Special thanks to Omar Hashim. You are super awesome >.< :DDD

      - Egg dropping again!!!!! Or is it coconut dropping?
      Check link below, brilliant tutorial: https://brilliant.org/wiki/egg-dropping/

      - Solve TIMUS 1223 first. It's the easier version.
      http://acm.timus.ru/problem.aspx?space=1&num=1223

      - The DP recurrence is very close to formula of binomial coefficient.
      We will pre-calculate the point in which the answer changes.
      DP[i][j] is the maximum answer height if we're allowed j drops with i eggs.

*/

#include <bits/stdc++.h>
using namespace std;

long long dp[64][2000001];

void init() {
      for (int i = 0; i <= 2000000; i++) {
            dp[1][i] = i;
      }
      for (int i = 1; i <= 63; i++) {
            dp[i][1] = 1;
      }
      for (int i = 2; i <= 63; i++) {
            for (int j = 2; j <= 2000000; j++) {
                  dp[i][j] = dp[i][j-1] + dp[i-1][j-1];
                  if (dp[i][j] > 2e18) dp[i][j] = 2e18;
            }
      }
}

void solve(long long n, long long k) {
      if (k == 1) {cout << n << '\n'; return;}
      if (k == 2) {
            long long x = sqrtl(n*2);
            while (x*(x+1)/2 < n) x++;
            cout << x << '\n';
            return;
      }
      long long lg = (63 - __builtin_clzll(n)) + 1;
      if (k >= lg) {cout << lg << '\n'; return;}

      cout << (upper_bound(dp[k], dp[k]+2000000, n) - dp[k] - 1) << '\n';
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);
      init();

      int t; cin >> t;
      while (t--) {
            long long n, k; cin >> n >> k;
            solve(n, k);
      }

      return 0;
}
