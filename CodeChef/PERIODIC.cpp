/*
      https://www.codechef.com/SNCK1A19/problems/PERIODIC/

      - First, let's just ignore all the -1, and consider every "adjacent" non-minus-one elements.
      It's not hard to see, the answer is infinity iff every adjacent elements are at their correct distance from each other.

      - The opposite case is also true. If there are any 2 elements which are not at correct distance, then answer cannot be infinity.

      - The brute force solution is to try all possible K and check if the array can "fit" in such K. This works in O(K*N)
      Can we do better than that? Yes we can.

      - Suppose there are 2 adjacent elements not at their correct distance from each other, then if K exists, it must lie somewhere in between these elements.
      Let's find the largest possible period that fits in between these two elements. Now we have a candidate for K.

      - Example: 3 and 2 are not at correct distance, candidate must be between them
                        |             |
                  ..... 3 -1 -1 -1 -1 2 .....
                                 |
      Largest possible K is 6, this is our candidate.

      - How does that help? It turns out that if K exists, then it must be either our candidate, or a divisor of our candidate.
      A number X can have at most logX divisors. Now our search space is very small, we can do brute force checking, but only on candidate divisors.

      - This problem helped me tremendously in finding the "divisor period" idea:
      https://codeforces.com/problemset/problem/582/C
*/

#include <bits/stdc++.h>
using namespace std;

int process(vector<pair<int, int>> b, int n) {
      if (n <= 1) return -1000000000;

      for (int i = 1; i < n; i++) {
            if (b[i].first - b[i-1].first == b[i].second - b[i-1].second) {
                  continue;
            } else {
                  int diff = b[i].second - b[i-1].second;
                  int k = diff + b[i-1].first - b[i].first;
                  return k;
            }
      }
      return -1000000000;
}

int check(vector<int> &a, int n, int k, int mx) {
      if (mx > k) return 0;

      int piv = 0;
      for (int i = 0; i < n; i++) {
            if (a[i] != -1) {piv = i+1; break;}
      }
      int start = (a[piv-1] - piv) % k;
      if (start < 0) start += k;

      for (int i = 0; i < n; i++) {
            if (a[i] != -1 && a[i] != start + 1) return 0;
            start = (start + 1) % k;
      }
      return 1;
}

void solve() {
      int n; cin >> n;
      vector<int> a(n);
      vector<pair<int, int>> b;
      for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != -1) {
                  b.push_back({a[i], i});
            }
      }

      int candidate = process(b, b.size());
      //cout << candidate << '\n';
      if (candidate == -1000000000) {
            cout << "inf\n"; return;
      }

      int ans = 0, mx = *max_element(a.begin(), a.end());
      for (int i = 1; i*i <= candidate; i++) {
            if (candidate % i == 0) {
                  int x = i;
                  int y = candidate/i;

                  if (check(a, n, x, mx)) ans = max(ans, x);
                  if (check(a, n, y, mx)) ans = max(ans, y);
            }
      }

      if (ans == 0) {cout << "impossible\n";}
      else {cout << ans << '\n';}
}

int main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int t; cin >> t;
      while (t--) {
            solve();
      }

      return 0;
}
