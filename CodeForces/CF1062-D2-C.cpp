/*
      https://codeforces.com/contest/1062/problem/D

      --> Tutorial: http://codeforces.com/blog/entry/63199
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll M = 1e9+7;

ll pw[100001];

void init() {
      pw[0] = 1;
      for (ll i = 1; i <= 100000; i++) {
            pw[i] = (pw[i-1] * 2) % M;
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);
      init();

      int n, q; cin >> n >> q;
      string s; cin >> s;
      vector<int> a(n+1);
      for (int i = 1; i <= n; i++) {
            a[i] = a[i-1] + (s[i-1] == '1');
      }

      while (q--) {
            int l, r; cin >> l >> r;
            ll o = a[r] - a[l-1];
            ll z = (r-l+1) - o;

            ll ans = pw[o] - 1;
            ll ans2 = 0;

            ans2 = ans * (pw[z] - 1);
            ans2 %= M;

            ll ans3 = ans+ans2;
            ans3 %= M;

            if (ans3 < 0) ans3 += M;
            cout << ans3 << '\n';
      }

      return 0;
}
