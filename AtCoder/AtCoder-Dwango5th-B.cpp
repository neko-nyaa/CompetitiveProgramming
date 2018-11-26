/*
      https://dwacon5th-prelims.contest.atcoder.jp/tasks/dwacon5th_prelims_b

      Editorial: https://img.atcoder.jp/dwacon5th-prelims/editorial.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n, k; cin >> n >> k;
      int sum = 0;
      vector<int> a(n);
      for (int i = 0; i < n; i++) {
            cin >> a[i];
      }

      vector<int> c;
      vector<int> ind;
      for (int i = 0; i < n; i++) {
            int tmp = 0;
            for (int j = i; j < n; j++) {
                  tmp += a[j];
                  ind.push_back(c.size());
                  c.push_back(tmp);
            }
      }

      int ans = 0;
      for (int b = 60; b >= 0; b--) {
            vector<int> bucket;
            for (int i: ind) {
                  if (c[i] & (1LL << b)) bucket.push_back(i);
            }
            if (bucket.size() >= k) {
                  ans |= (1LL << b);
                  swap(ind, bucket);
            }
      }
      cout << ans;

      return 0;
}
