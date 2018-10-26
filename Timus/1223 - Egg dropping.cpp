/*
      http://acm.timus.ru/problem.aspx?space=1&num=1223

      - How did professor Bohr escape the anger of the eagle anyway?

      - Brilliant link for a brilliant problem:
      https://brilliant.org/wiki/egg-dropping

      - I think it explains it really well. The only other optimization to note is, given enough eggs, the best strategy is to do binary search.
      So if we are given too many eggs, then it's the same as given just enough eggs. Now our constrain is drastically reduced.
*/

#include <bits/stdc++.h>
using namespace std;

int ans[1003][1003];

void init() {
      for (int i = 0; i <= 1000; i++) {
            for (int j = 0; j <= 60; j++) {
                  ans[i][j] = 5000;
            }
      }

      for (int i = 0; i <= 60; i++) {
            ans[0][i] = 0;
      }

      for (int i = 1; i <= 1000; i++) {
            for (int j = 1; j <= 60; j++) {
                  for (int k = 1; k <= i; k++) {
                        ans[i][j] = min(ans[i][j], max(ans[k-1][j-1], ans[i-k][j]) + 1);
                  }
            }
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);
      init();

      int n, k;
      while (cin >> k >> n, k, n) {
            k = min(k, 60);
            cout << ans[n][k] << '\n';
      }

      return 0;
}
