/*
      https://codeforces.com/contest/1060/problem/D

      - Sample test 2 was actually a huge hint, that we can "connect" 2 guests together with L of guest 1 and R of guest 2.

      - The cost of such "connection" is equal to max(L_1, R_2). We can even connect one guest with himself.

      - We will need to do N connections, and we want the total cost to be minimal.

      - We will do this greedily. Sort all the L and R values. The answer will be sum of max(L_i, R_i) over all i.
      It is not hard to prove that, doing any other way can only make the answer worse.

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      vector<ll> a(n), b(n);
      for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
      }
      sort(a.begin(), a.end());
      sort(b.begin(), b.end());

      ll ans = n;
      for (int i = 0; i < n; i++) {
            ans += max(a[i], b[i]);
      }
      cout << ans;

      return 0;
}
