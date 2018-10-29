/*
      https://tenka1-2018.contest.atcoder.jp/tasks/tenka1_2018_d

      - Let's look at the conditions from the statements:
            + Each of the integers must be in exactly two sets
            + Any two of the sets have exactly one number in common
      - Let's imagine each set as a graph vertex. Two vertices are connected if there is a number in common.

      - So we can rephrase the question like this:
            "Construct a complete graph with N edges"
      - Much easier now is it? :D

      - A complete graph with K vertices have K*(K-1)/2 edges. So we can brute force to find our K, or "No" if it doesn't exist.
      If we found our K, we can add a number to every pair of vertices in this graph.
      We have 1e5 edges, so it will run in time.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve(int n) {
      cout << "Yes\n" << n << '\n';

      vector<int> ans[n+1]; int k = 1;
      for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                  ans[i].push_back(k);
                  ans[j].push_back(k);
                  k++;
            }
      }

      for (int i = 1; i <= n; i++) {
            cout << n-1 << ' ';
            for (int j: ans[i]) cout << j << ' ';
            cout << '\n';
      }

      exit(0);
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      for (int i = 1; i <= 1000; i++) {
            if (i*(i-1)/2 == n) {
                  solve(i);
            }
      }

      cout << "No";

      return 0;
}
