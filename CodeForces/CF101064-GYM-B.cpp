/*
      https://codeforces.com/gym/101064/problem/B
      --> Tutorial: https://linux.ime.usp.br/~yancouto/2016-WIP-Tutorial.pdf

      - The problem is essentially count number of permutations of length N, with longest increasing sequence (LIS) of length 3 or 4.

      - Let's look at how we do the classic LIS problem. We have our input array, and the LIS array constructed so far.
      When we arrive at an element arr[i], we replace arr[i] with some LIS[j] > arr[i], and push it when arr[i] is larger than LIS[last]

      - This gives a hint on how we can construct a valid permutation. If we have our current LIS array, we can determine how many choices we have to "replace" LIS[i]
      Let's take an example. We will construct an array with N = 6.
            + Initially our LIS is empty:                                           [x, x, x, x].
              The number of choices to insert a number into the i-th position is:   [6, 0, 0, 0]
              Six choices to insert a number into the 1st position

            + Suppose we decide to insert number 2:                                 [2, x, x, x]
              Then, the choices [3, 4, 5, 6] will get transferred to the second position. The choices [1] stays in the second.
              Our new list of choice count are:                                     [1, 4, 0, 0]
              One choice of inserting into the first position, and 4 choices of inserting into the second.

            + Suppose next we insert 4:                                             [2, 4, x, x]
              The choices [5, 6] gets transferred to position 3:                    [1, 1, 2, 0]

      - As we insert new elements, some number of choices will get transferred to the next position.

      - Let's define dp[c1][c2][c3][c4][flag] as our choice array [c1, c2, c3, c4], and flag denoting whether our LIS has length greater than 2 yet.
      We can iterate over all choices of c1, c2, c3, and c4, and make the choice-transferring accordingly.

      - We have O(N^4) states, and for each state we will iterate over O(N) choices left, so our final time complexity of O(N^5)
      Memory complexity is O(N^4)
*/

#include <bits/stdc++.h>
using namespace std;

long long M = 1e9+7;

int n;
int dp[61][61][61][61][2];

int solve(int c1, int c2, int c3, int c4, int flag) {
      if (c1 + c2 + c3 + c4 == 0) {
            return flag;
      }

      if (dp[c1][c2][c3][c4][flag] != -1) {
            return dp[c1][c2][c3][c4][flag];
      }

      int ans = 0;
      for (int i = 1; i <= c1; i++) {
            ans += solve(i - 1, c2 + c1 - i, c3, c4, flag); ans %= M;
      }
      for (int i = 1; i <= c2; i++) {
            ans += solve(c1, i - 1, c3 + c2 - i, c4, flag); ans %= M;
      }
      for (int i = 1; i <= c3; i++) {
            ans += solve(c1, c2, i - 1, c4 + c3 - i, 1); ans %= M;
      }
      if (c4 >= 1) {
            ans += solve(c1, c2, c3, c4 - 1, 1); ans %= M;
      }

      return dp[c1][c2][c3][c4][flag] = ans;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n;
      long long ans = 1;
      for (int i = 1; i <= n; i++) {
            ans = (ans*i) % M;
      }
      memset(dp, -1, sizeof(dp));

      long long actual_ans = (ans - solve(n, 0, 0, 0, 0)) % M;

      while (actual_ans < 0) actual_ans += M;
      cout << actual_ans;

      return 0;
}
