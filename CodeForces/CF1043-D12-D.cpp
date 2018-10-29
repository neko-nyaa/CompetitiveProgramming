/*
      https://codeforces.com/contest/1043/problem/D

      - Deleting some prefix and suffix is essentially taking a subarray. So we rephrase the statement like this:
            "Given M permutations, each with N elements, count subarrays such that they appear in every of the M permutations"
      - From this point on I will call these subarrays "common".

      - Let's make an observation: if A[L..R] is common, then A[L+1..R] and A[L..R-1] (subarrays of that subarray) are also common. And vice-versa.
      This gives us an important detail: All common subarrays are disjoint.

      - A few examples:
            + Example test 1: [1, 2, 3] and [2, 3, 1], we can split them into [1] and [2, 3]. They are common in both arrays.
            + My own example: [3, 4, 6, 1, 5, 2] and [2, 6, 1, 5, 3, 4], split them into [3, 4], [6, 1, 5], and [2].

      - Now we know what to do. We can work on the arrays one by one, and keep splitting our list of subarrays.
      The splitting is just implementation. There are so many ways to do this. I use a DP-like approach, while the editorial suggests two-pointers.

      - Be careful! Intended solution is O(N*M), and the constrain of 1 million numbers in 1 second leaves very little (if not too little) room for log factors.

      - Editorial: https://codeforces.com/blog/entry/62797
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;

void normalize(vector<vector<int>> &split) {
      vector<vector<int>> ans;
      vector<int> a(n), ind(n+1);
      for (int i = 0; i < n; i++) {
            cin >> a[i];
            ind[a[i]] = i;
      }

      for (auto b: split) {
            vector<int> k;
            for (int i: b) {
                  if (k.empty()) k.push_back(i);
                  else {
                        if (ind[k.back()] != ind[i] - 1) {
                              ans.push_back(k);
                              k.clear();
                              k.push_back(i);
                        } else {
                              k.push_back(i);
                        }
                  }
            }
            if (k.size()) ans.push_back(k);
      }

      ans.swap(split);
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n >> m;
      vector<int> a(n), ind(n+1);
      for (int i = 0; i < n; i++) {
            cin >> a[i];
            ind[a[i]] = i;
      }

      vector<vector<int>> split;
      split.push_back(a);
      for (int turn = 1; turn < m; turn++) {
            normalize(split);
      }

      int ans = 0;
      for (int i = 0; i < split.size(); i++) {
            int ss = split[i].size();
            ans += ss*(ss-1)/2 + ss;
      }
      cout << ans;

      return 0;
}
