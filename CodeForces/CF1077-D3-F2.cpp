/*
	https://codeforces.com/contest/1077/problem/F2
	--> Editorial: https://codeforces.com/blog/entry/63274

	- In this problem, we are given array of positive integers. We must pick some numbers so that:
		+ We pick exactly X numbers.
		+ In each subarray of size K, at least one number must be picked.
		+ The sum of our picked number is largest possible
	- Let's rephrase the second condition as follow:
		+ We are not allowed to skip K or more numbers per picking.

	- Define dp[i][j] as the maximum sum when:
		+ i is the last reposted picture
		+ j is the number of reposted done
	We will want the maximum value of dp[i][X] with i from N-K+1 to N. 

	- Suppose we know all values of dp[][j - 1], we want to use it to calculate dp[][j]. What will the transition be?
		+ dp[i][j] = a[i] + max(dp[i - p][j - 1] from p = 1 to K)
	  Therefore, we have O(NX) DP states, and each can be calculated in O(K). We have obtained O(NKX) solution for F1.

	- Can we optimize this up for F2? Yes we can. 

	- Notice how "max(dp[i - p][j - 1] from p = 1 to K)" is actually a sliding window maximum of fixed size.
	So we can use a deque (or two stacks/queues) and perform the sliding window, allowing for calculation in O(1)
	Now each O(K) calculation is done in O(1), we obtain O(NX) solution.

	- Helpful link: https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
	Editorial explains it really well too.
	
	- Some data structures like range max query or multiset can also help with sliding window as well, but they may or may not be fast enough.
	My sliding window solution with multiset gives TLE.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k, x;
ll dp[5008][5008];
ll a[5008];

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> k >> x;
      if (n > k*(x+1) - 1) {cout << -1; return 0;}
      for (int i = 1; i <= n; i++) {
            cin >> a[i];
      }

      for (int j = 1; j <= x; j++) {

            deque<ll> dq;
            for (int i = max(0, j - k); i < j; i++) {
                  while (!dq.empty() && dp[i][j-1] >= dp[dq.back()][j-1]) {
                        dq.pop_back();
                  }
                  dq.push_back(i);
            }

            for (int i = j; i <= min(n, j*k); i++) {
                  dp[i][j] = a[i] + dp[dq.front()][j-1];

                  while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
                  while (!dq.empty() && dp[i][j-1] >= dp[dq.back()][j-1]) dq.pop_back();

                  dq.push_back(i);
            }
      }

      ll ans = 0;
      int left = n-k+1;
      int right = min(n, x*k);

      for (int i = left; i <= right; i++) {
            ans = max(ans, dp[i][x]);
      }
      cout << ans;

      return 0;
}