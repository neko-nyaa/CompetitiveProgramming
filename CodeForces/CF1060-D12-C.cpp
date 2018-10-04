/*
      https://codeforces.com/contest/1060/problem/C

      - By analyzing the formula, we can quickly realize the sum for each sub-rectangle is the product
      of the sum of numbers on the two sides of the sub-rectangle.
      This suggests we need to build some prefix-sum of the rectangle sides.

      - The numbers in the input are all positive, so the prefix-sum is strictly monotonic.
      This suggests a binary search or two-pointers approach can be used.

      - Let's call the optimal sub-rectangle's sides be W and H, corresponding to array A and B, respectively.
      We will iterate on value W.

      - Suppose the value W is fixed, with sum of numbers on its side be X. Obviously we want X to be as small as possible.

      - Once we have found the smallest X, we will find the largest possible window H with sum Y, such that X*Y does not exceed x from input.
      It can be solved with binary search or two-pointers.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      ll n, m;
      cin >> n >> m;
      vector<ll> a(n+1), b(m+1);
      for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += a[i-1];
      }
      for (int i = 1; i <= m; i++) {
            cin >> b[i];
      }
      ll x; cin >> x;


      ll ans = 0;
      for (ll k = 1; k <= n; k++) {
            vector<ll> s;
            for (ll i = k; i <= n; i++) {
                  s.push_back(a[i] - a[i-k]);
            }
            sort(s.begin(), s.end());

            ll sz = x/s[0];

            ll petr1 = 1, petr2 = 1;
            ll sum = 0;
            while (petr2 <= m) {
                  sum += b[petr2];
                  petr2++;

                  while (sum > sz) {
                        sum -= b[petr1];
                        petr1++;
                  }

                  ans = max(ans, k*(petr2 - petr1));
            }
      }
      cout << ans;

      return 0;
}
