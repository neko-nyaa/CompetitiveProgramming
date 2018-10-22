/*
      http://community.topcoder.com/stat?c=problem_statement&pm=11357&rd=14431

      - Have you ever tried doing a codeforces round backwards, say, from problem C down to A, because you get more points that way?
      This problem uses the same idea, and is very similar to the greedy "tasks and deadlines" job scheduling problem.

      - Let's solve the scheduling problem first. Suppose we must do every tasks, and our T is infinite, what is the optimal order?
      This is a very classic task :D google gives a lot of results.

      - It turns out, we only need to sort the tasks by their ratio of requiredTime by their pointsPerMinute, and completely ignore their maxPoints.
      If we're going to do any tasks at all, we would want to do them in that exact order. So let's sort them by that order.

      - Let's come back to the original problem. We know in what order we should solve tasks, now the question is just whether to solve it or not.

      - We can do dynamic programming, dp[i][j] will be the maximum score we earn at time i, if we consider only the first j tasks.
      This is a knapsack DP, can be done with dp[T][tasks_count].
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int cmp(tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {
      ll x, y, z, p, q, r;
      tie(x, y, z) = a;
      tie(p, q, r) = b;

      return y*r > q*z;
}

class TheProgrammingContestDivOne{
public:
      ll dp[100001][51];

	int find(int T, vector<int> maxPoints, vector<int> pointsPerMinute, vector<int> requiredTime) {
            int n = maxPoints.size();
            vector<tuple<ll, ll, ll>> a;
            for (int i = 0; i < n; i++) {
                  a.push_back(make_tuple(maxPoints[i], pointsPerMinute[i], requiredTime[i]));
            }
            sort(a.begin(), a.end(), cmp);

            ll ans = 0;
            for (int i = 1; i <= n; i++) {
                  ll x, y, z;
                  tie(x, y, z) = a[i-1];

                  for (int j = 0; j <= T; j++) {
                        dp[j][i] = dp[j][i-1];
                        if (j - z >= 0) dp[j][i] = max(dp[j][i], dp[j - z][i-1] + x - y*j);
                        ans = max(ans, dp[j][i]);
                  }
            }
            return ans;
	}
};
