/*
      https://codeforces.com/contest/1043/problem/E

      - In this problem, we are given two arrays X and Y, and are asked to sum min(X[i] + Y[j], X[j] + Y[i]) for all pairs of i, j.
      Let's ignore the invalid pairs U and V for now, we will subtract them later.

      - We can't add all of them in O(N^2). Is there a way we can just simply get the score sum for a participant faster?

      - Let's do some math. Suppose we have:
            X[i] + Y[j] < X[j] + Y[i]     (that means min(X[i] + Y[j], X[j] + Y[i]) is the first pair)
        Then we have:
            X[i] - X[j] < Y[i] - Y[j]
        So their difference matters a lot in determining which pair to take!!!

      - Let's sort X and Y by their differences. Then calculate prefix sum of our sorted X and Y.
      Now we can just simply get the score sum for a participant in O(1) 

      - Now we work on U and V pairs. Just subtract min() from them and we're done. There are only 300k pairs.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n, m; cin >> n >> m;
      vector<tuple<int, int, int, int>> tp(n);
      vector<int> k(n), kk(n);
      for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            int z = y - x;
            k[i] = x; kk[i] = y;
            tp[i] = make_tuple(z, x, y, i);
      }
      sort(tp.begin(), tp.end());

      vector<int> x(n), y(n), id(n), xx(n), yy(n);
      for (int i = 0; i < n; i++) {
            int a, b, c, d;
            tie(a, b, c, d) = tp[i];
            x[i] = b, y[i] = c, id[i] = d;
      }
      xx = x; yy = y;
      for (int i = 1; i < n; i++) {
            y[i] += y[i-1];
      }
      for (int i = n-2; i >= 0; i--) {
            x[i] += x[i+1];
      }

      vector<int> ans(n);
      for (int i = 0; i < n; i++) {
            int ind = id[i];
            if (i > 0) {
                  ans[ind] += xx[i]*i + y[i-1];
            }
            if (i < n-1) {
                  ans[ind] += yy[i]*(n-i-1) + x[i+1];
            }
      }

      while (m--) {
            int u, v; cin >> u >> v;
            u--; v--;
            int kkk = min(k[u] + kk[v], kk[u] + k[v]);
            ans[u] -= kkk;
            ans[v] -= kkk;
      }

      for (int i: ans) cout << i << ' ';

      return 0;
}
