/*
      https://hanoi18.kattis.com/problems/hanoi18.dividedoughnut
      This is one of the problems where the constrain is so tight it requires absolute optimization.

      - The key to this problem is intermediate value theorem. Suppose there is a function f() takes a domain [a, b].
      If this function takes values f(a) and f(b) at each endpoints, then every values between f(a) and f(b) must appear at some point in the domain.

      - Link for reference: https://en.wikipedia.org/wiki/Intermediate_value_theorem

      - How does it relate to this problem? Let's define a function F(X) = query(X, X + half-donut), which is the sprinkle count of half a donut starting from X.
      Suppose X moves by one unit, then F(X) can move by at most one unit ---> F(X) is a continuous function.
      We know the range of F(X) is [0, n]. By intermediate value theorem, F(X) = n/2 must appear at some point in our domain.
      Therefore, answer is always YES. We just have to find our value X.

----------------------------------------------------- Let's get to the actual solving ---------------------------------------------------------------

      - There's a clear solution at this point. We will do binary search on the domain. A domain [a, b] is valid iff F(X) = n/2 is an intermediate value
      in the domain. So we can keep cutting off invalid halves of the domain.

      - Worst case is when n = 2. We get 30 queries, including the answer. So we can ask 29 questions at most.
      We also need one question at F(0), to see whether there's an intermediate value.

      - This leaves us with 28 queries, which is 2 queries short to do a binary search over the domain [0, 1e9). Let's see how we can optimize it.
            + Suppose there is a value X where F(X) = n/2, then F(X + half_donut) = n/2 also holds. Therefore there is at least one valid X in range [0, 5e8).
              We will only have to binary search on this range. Now we've cut down our domain by half without needing a query.
            + Suppose we have cut down our domain [a, b] to the point where (b - a) <= 2, and we know F(a) and F(b) are both not n/2.
              Then it must be true that X = (a+b)/2, and F(X) = n/2. So we don't have to question that domain anymore, and just answer straight away.

      - We have saved ourselves 2 queries, which leaves us just enough room to solve this problem.
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int N = 1e9;
int n;

void answer(int x) {
      cout << "YES" << " " << x << endl;
      exit(0);
}

int query(int x) {
      int k = (x + N/2 - 1) % N;

      cout << "QUERY " << x << ' ' << k << endl;
      int ans; cin >> ans;
      if (ans == n/2) answer(x);
      return ans;
}

signed main() {
      //ios::sync_with_stdio(0); cin.tie(0);

      cin >> n;

      int left = 0, right = N/2;
      int val = query(0);

      int queries_left = 28;
      while (queries_left--) {
            int mid = (left + right)/2;

            int valmid = query(mid);

            if ((valmid < n/2 && val > n/2) || (valmid > n/2 && val < n/2)) {
                  right = mid - 1;
            } else {
                  left = mid + 1;
            }
      }
      answer((left + right)/2);

      return 0;
}
