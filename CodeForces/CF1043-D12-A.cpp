/*
      https://codeforces.com/contest/1043/problem/A

      - We can notice that answer cannot exceed 201, so we can just brute force every values and check if it is valid.

      - Be careful of
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      int s = 0;
      vector<int> a(n);
      for (int i = 0; i < n; i++) {
            cin >> a[i];
            s += a[i];
      }

      for (int k = *max_element(a.begin(), a.end()); 1; k++) {
            int t = 0;
            for (int i = 0; i < n; i++) {
                  t += k - a[i];
            }
            if (t > s) {
                  cout << k; return 0;
            }
      }

      return 0;
}
