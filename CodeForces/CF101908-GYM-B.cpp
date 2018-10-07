/*
      https://codeforces.com/gym/101908/problem/B

      - We will need Sprague-Grundy theorem for this.

      - We know for every starting square (X, Y) such that X = 0 or Y = 0 or X = Y, it's a win square.

      - Let's calculate Grundy number for every other squares.

      - The Grundy number of a square is the MEX value of all its reachable squares.
      The constrains are very small, so this value can be found with brute force.

      - Then it's just the xor-sum of all the Grundy numbers of chosen squares in the input.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int dp[208][208];

void init() {
      for (int i = 1; i <= 100; i++) {
            dp[0][i] = dp[i][0] = dp[i][i] = 500;
      }

      for (int i = 1; i <= 100; i++) {
            for (int j = 1; j <= 100; j++) {
                  if (i != j) {
                        vector<bool> s(600);
                        for (int a = 1; a < i; a++) {
                              s[dp[a][j]] = 1;
                        }
                        for (int a = 1; a < j; a++) {
                              s[dp[i][a]] = 1;
                        }
                        for (int a = 1; a <= min(i, j); a++) {
                              s[dp[i-a][j-a]] = 1;
                        }
                        for (int a = 0; a <= 200; a++) {
                              if (!s[a]) {dp[i][j] = a; break;}
                        }
                  }
            }
      }
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
      init();

      int ans = 0;
      int n; cin >> n;
      for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            if (x == y) {cout << 'Y'; return 0;}
            ans ^= dp[x][y];
      }
      if (ans) cout << 'Y'; else cout << 'N';

	return 0;
}
