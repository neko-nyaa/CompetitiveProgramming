/*
      https://dwacon5th-prelims.contest.atcoder.jp/tasks/dwacon5th_prelims_c

      Editorial: https://img.atcoder.jp/dwacon5th-prelims/editorial.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n; string s;

void solve() {
      int k; cin >> k;
      int ans = 0;

      int mcur = 0, dcur = 0;
      int ccur = 0;
      for (int i = 0; i < k; i++) {
            if (s[i] == 'D') {
                  dcur++;
            } else if (s[i] == 'M') {
                  mcur++;
                  ccur += dcur;
            } else if (s[i] == 'C') {
                  ans += ccur;
            }
      }

      for (int i = k; i < n; i++) {
            if (s[i-k] == 'D') {
                  ccur -= mcur;
                  dcur--;
            } else if (s[i-k] == 'M') {
                  mcur--;
            } else if (s[i-k] == 'C') {

            }

            if (s[i] == 'D') {
                  dcur++;
            } else if (s[i] == 'M') {
                  mcur++;
                  ccur += dcur;
            } else if (s[i] == 'C') {
                  ans += ccur;
            }
      }
      cout << ans << '\n';
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> s;
      int q; cin >> q;
      while (q--) {
            solve();
      }

      return 0;
}
