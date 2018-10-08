/*
      https://codeforces.com/contest/1033/problem/C

      - This is a classic game state DP problem.

      - The basic idea of game states: If we can move the piece to a losing position, our position is a win.

      - Let's iterate from N down to 1 and check, from this starting state, if we can reach a losing state.
      The complexity might seem O(N^2), but the harmonic sum (1/i) is equal to logN, so it's actually O(NlogN)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      vector<int> a(n+1), ind(n+1);
      for (int i = 1; i <= n; i++) {
            cin >> a[i];
            ind[a[i]] = i;
      }

      vector<char> ans(n+1, 'A');
      ans[n] = 'B';
      for (int i = n-1; i > 0; i--) {
            int b = 1;
            int k = ind[i];
            for (int j = k; j <= n; j += i) {
                  if (a[j] > i && ans[a[j]] == 'B') {b = 0; break;}
            }
            for (int j = k; j > 0; j -= i) {
                  if (a[j] > i && ans[a[j]] == 'B') {b = 0; break;}
            }
            if (b) ans[i] = 'B';
            else ans[i] = 'A';
      }

      for (int i = 1; i <= n; i++) {
            cout << ans[a[i]];
      }

	return 0;
}
