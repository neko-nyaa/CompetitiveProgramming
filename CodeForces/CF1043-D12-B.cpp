/*
      https://codeforces.com/contest/1043/problem/B

      - Let's add a 0 to the beginning of the array A, and try to recreate array X.
      For sample test 2, the initial array is:
            0 1 3 5 6 8
      We will build the "difference array", that is, the difference between every consecutive elements in A:
            1 2 2 1 2

      - Let's check for every prefixes of this array X, to see if it can be the "period" of the entire array. Checking can be done in O(N)

      - So our time complexity is O(N^2).

-----------------------------------------------------------------EXTRA NOTES---------------------------------------------------------------------------

      - This problem can be solved with Z-function for larger N as well. We will build a Z-array for the array X, and check every prefixes as usual.
      The complexity will be O(N) for the Z-array, and O(NlogN) for the checking. Thus we achieve O(NlogN) complexity.

      - Helpful tutorial on Z-function:
                  https://cp-algorithms.com/string/z-function.html
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int check(vector<int> &a, int k, int n) {
      for (int i = 0; i < n; i++) {
            if (a[i] != a[i % k]) return 0;
      }
      return 1;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      vector<int> b(n+1), a(n);
      for (int i = 1; i <= n; i++) {
            cin >> b[i];
            a[i-1] = b[i] - b[i-1];
      }

      vector<int> ans;
      for (int i = 1; i <= n; i++) {
            if (check(a, i, n)) ans.push_back(i);
      }

      cout << ans.size() << '\n';
      for (int i: ans) cout << i << ' ';

      return 0;
}
