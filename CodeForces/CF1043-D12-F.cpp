/*
      https://codeforces.com/contest/1043/problem/F

      - THIS IS A NON-DETERMINISTIC SOLUTION. Author's solution here: https://codeforces.com/blog/entry/62797

      - In this problem we are asked to find the minimal size subset which GCD is equal to 1.

      - Let's assume that the answer exists (we can easily check otherwise), we will use randomized approach for this.

      - There are several ways we can reduce the search space:
            + We will take only one instance of each number. It doesn't make sense when we take the same number multiple times.
            + We will delete all numbers which are multiples of another one. For example if we have 3 and 6, then it's never optimal to take 6.
        The constrain on elements is 300000, so careful implementation and it won't be time-costly.

      - We will now take elements at random. Initialize the variable "ans" equal to N. We will keep taking new elements, as long as:
            + So far we have taken less elements than the current "ans". We already know the minimal set so far is "ans", it doesn't make sense to take more.
            + The GCD of the current set is not 1.
        If the GCD of the set is 1, update the answer as needed.

      - I have used 1 million rounds of random, it runs in just over 2 seconds. Time complexity is either undefined, or I just have no idea what it is.

      - This solution uses Mersenne Twister random number generator. You can read more about it here:
            https://codeforces.com/blog/entry/61587
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      set<int> s;
      int g = 0;
      while (n--) {
            int x; cin >> x;
            s.insert(x);
            g = __gcd(g, x);
      }
      if (g != 1) {cout << -1; return 0;}

      for (auto it = s.begin(); it != s.end(); it++) {
            for (int j = 2*(*it); j <= 300000; j += *it) {
                  if (s.find(j) != s.end()) s.erase(j);
            }
      }

      vector<int> a(s.begin(), s.end());
      n = a.size();
      if (a[0] == 1) {cout << 1; return 0;}

      int ans = n;
      for (int t = 0; t <= 1000000; t++) {
            set<int> st;
            int g = 0;
            while (g != 1 && st.size() < ans) {
                  int k = uniform_int_distribution<int>(0, n-1)(rng);
                  st.insert(k);
                  g = __gcd(g, a[k]);
            }
            ans = min(ans, int(st.size()));
      }
      cout << ans;

      return 0;
}
