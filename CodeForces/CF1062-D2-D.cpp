/*
      https://codeforces.com/contest/1062/problem/D
      --> Tutorial: http://codeforces.com/blog/entry/63199
      The author uses an Euler-cycle approach. I used a different one, which I'll describe here

      - The answer is either:
            + The sum of divisors of i (except 1 and itself) for all i from 2 to N, times 4. Or
            + Define f(i) the sum of all numbers from 2 to k, such that k*i <= N. Answer is all f(i) from i = 2 to N, times 4.

      - How do we achieve so? The obvious thing is to start with number 2. All other starting positions can only make our answer worse.

      - The sample explanation was a tremendous help. In the first sample, we can move in a "cycle" and back to the starting square.
      That means, if a number is reachable from another, then we can move between them in a cycle, 4 moves. So now our graph consists of many cycles.
      In fact, the idea of cycle-combining is the basis of finding Euler path.

      - So now we know we can "join" cycles together and take all of their scores, the matter is just how to move optimally.

      - Let's be greedy. We know we can move from A to B if A is a multiple, or a factor of B. To avoid repeat, we will move in only one direction (factors only or multiples only).
      If a number is reachable, then let's reach it from its furthest possible number, then reach all of its divisors of multiples.

      - But how do we subtract the unreachable numbers? Notice that, unreachables can only be odd primes greater than N/2.
      Because they are prime, the only divisors they have are 1 and itself. So even if we count them, they contribute nothing.
      Because they are greater than N/2, they can't be reached by any even numbers. So they have no multiples to contribute.

      - This alone is enough to solve the problem. The constrain is small, we can implement an O(N) or O(NsqrtN) and it will pass safely.

----------------------------------------------------------BONUS--------------------------------------------------------------------

      - This code uses an O(sqrtN) idea for counting sum of divisors. Can you see how? :D

      - "Sum of divisors" problem, with a tighter constrain: https://cses.fi/problemset/task/1082
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll calc(ll l, ll r) {
      ll ansr = r * (r+1)/2;
      ll ansl = l * (l+1)/2;
      ll ans = (ansr - ansl);
      return ans;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      ll n; cin >> n;
      ll ans = 1;
      for (ll i = 1;;) {
            ll hi = n/i, lo = n/(i+1);
            ans += i*calc(lo, hi);
            if (lo == 0) break;
            i = n/lo;
      }

// remove the 2 lines below if you just want sum of divisors
      ans -= n;
      ans -= n*(n+1)/2;

      cout << ans*4;

	return 0;
}
