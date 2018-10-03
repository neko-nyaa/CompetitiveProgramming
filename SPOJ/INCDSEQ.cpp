/*
      https://www.spoj.com/problems/INCDSEQ/

      - The idea was extended from INCSEQ. This time data compression was necessary.

      - INCSEQ code: https://github.com/nya-nya-meow/CompetitiveProgramming/blob/master/SPOJ/INCSEQ.cpp

      - The recurrence is the same as INCSEQ, this time answer for all dp[][] has to be stored.

      - Instead of finding all sum of dp[j][k-1] as normal, we find how much dp[j][k-1] increases since the last time we encountered element j.

      - In fact only 3 lines were modified compared to INCSEQ.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
int M = 5000000;

int n, k;
int tree[52][300001];
int dp[52][30001];

void update(int ind, int val, int i) {
      while (ind <= n) {
            tree[i][ind] = (tree[i][ind] + val) % M;
            ind += ind & (-ind);
      }
}

int query(int ind, int i) {
      int ans = 0;
      while (ind > 0) {
            ans = (tree[i][ind] + ans) % M;
            ind -= ind & (-ind);
      }
      return ans;
}

void compress(vector<int> &a) {
      vector<int> b = a;
      sort(b.begin(), b.end());
      map<int, int> m;
      for (int i = 1, c = 1; i <= n; i++) {
            if (m.find(b[i]) == m.end()) m[b[i]] = c++;
      }
      for (int i = 1; i <= n; i++) {
            a[i] = m[a[i]];
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> k;

      vector<int> a(n+1);
      for (int i = 1; i <= n; i++) {
            cin >> a[i];
      }
      compress(a);

      if (k == 1) {
            set<int> s;
            for (int i = 1; i <= n; i++) s.insert(a[i]);
            cout << s.size(); return 0;
      }

      int ans = 0;
      for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                  int p = ((j == 1 ? 1 : query(a[i] - 1, j-1)) - dp[j][a[i]] + M) % M;
                  dp[j][a[i]] = (dp[j][a[i]] + p) % M;

                  update(a[i], p, j);
                  if (j == k) ans = (ans + p) % M;
                  if (ans < 0) ans += M;
            }
      }
      cout << ans;

      return 0;
}
