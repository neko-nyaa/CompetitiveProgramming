/*
      https://www.codechef.com/problems/COINDENO
      https://codeforces.com/blog/entry/60701?#comment-446462     <---- helpful explanation

      - Another coin change DP? Yes.

      - Note that this solution uses int128, which will not work on windows compilers, such as on codeforces.

      - For the first subtask, we will do a regular knapsack DP. The queries are low enough to be stored in an array, so we can store all the answers.

      - How will we extend this to the 2nd subtask? We can see that, when the queries become too large, it is optimal to take a pre-calculated smaller value,
      and fill it up by adding a single coin type. We can find the largest value in the DP table that is reachable for each coin value.
      With this, we can answer the queries in O(N).

      - This requires careful implementation, as int128 and modulo operations are very costly, so they can give TLE!!!
*/

#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;

long long M = 1e9+7;
const int MX = 1000000;

void read(__int128_t &a) {
      long long k; cin >> k;
      a = k;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n, c, q;
      cin >> n >> c >> q;

      ll INF = 1e18;
      ll LINF = 1e36;
      vector<long long> dp(MX+1, INF);
      dp[0] = 0;
      vector<long long> a;
      vector<ll> w;
      for (int j = 0; j < n; j++) {
            int x; long long y; cin >> x >> y;
            for (int i = x; i <= MX; i++) {
                  dp[i] = min(dp[i], dp[i - x] + y);
            }
            a.push_back(x);
            w.push_back(y);
      }

      while (q--) {
            long long m; cin >> m;
            if (m <= MX) {
                  if (dp[m] == INF) cout << "-1\n";
                  else cout << (dp[m] % M) << '\n';
            } else {
                  ll ans = LINF;
                  for (int i = 0; i < n; i++) {
                        long long k = m % a[i];
                        long long j = (MX/a[i] - 1)*a[i] + k;

                        if (dp[j] == INF) continue;

                        ans = min(ans, dp[j] + w[i]*((m - j)/a[i]));
                  }
                  if (ans == LINF) cout << "-1\n";
                  else cout << (long long)(ans % M) << '\n';
            }
      }

      return 0;
}
