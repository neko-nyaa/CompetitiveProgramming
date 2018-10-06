/*
      https://codeforces.com/contest/1059/problem/C

      - Notice how most of the time the GCD of the array is 1.

      - If we want the maximum lexicographical order, we would want to increase the array GCD as soon as possible.

      - To increase the GCD of the array to a value X, we will have to remove all numbers that are not a divisor of X.
      The fastest way to do this is pick X = 2*current GCD. We will remove the numbers in the odd positions.

      - Be careful of the case when our array have 3 numbers left, in which case it's optimal to pick X = 3*current GCD
      and remove the first 2 numbers.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      vector<int> ans;
      int left = n;
      for (int i = 1; i <= n; i *= 2) {
            if (left == 3) {
                  ans.push_back(i);
                  ans.push_back(i);
                  ans.push_back(i*3);

                  break;
            }

            for (int j = i; j <= n; j += i*2) {
                  ans.push_back(i);
                  left--;
            }
      }

      for (int i: ans) cout << i << " ";

	return 0;
}
