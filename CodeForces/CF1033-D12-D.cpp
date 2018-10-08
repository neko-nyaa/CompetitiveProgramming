/*
      https://codeforces.com/contest/1033/problem/D

      - To count number of divisors of a number, we will need to have all the powers of the number's prime factor.
      Notice how we only need the power, but not the factor itself.

      - Each number has 3, 4, or 5 divisors. So it must have the form p^2, p^3, p^4, or p*q, with p and q primes.
      The first 3 cases can be checked easily. Now we have to handle the last case.

      - Pollard-Rho to find divisors won't be fast enough, we will need to somehow get around it.

      - Let's build a table g[][], where g[i][j] = GCD(a[i], a[j]). From this table, we can easily factorize a number.

      - There will still be some numbers left not factorized, but at this point we can safely assume the two prime factors
      do not appear anywhere else besides this number itself.

      - Now we have obtained all the powers, and we can calculate the answer.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      map<ll, ll> div;
      vector<ll> a;
      while (n--) {
            ll x; cin >> x;
            ll k1 = sqrtl(x);
            ll k2 = sqrtl(k1);
            ll kc = cbrtl(x);

            if (kc*kc*kc == x) {
                  div[kc] += 3;
                  continue;
            }

            if (k2*k2*k2*k2 == x) {
                  div[k2] += 4;
                  continue;
            }

            if (k1*k1 == x) {
                  div[k1] += 2;
                  continue;
            }

            a.push_back(x);
      }
      n = a.size();

      ll g[n][n];
      for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                  g[i][j] = __gcd(a[i], a[j]);
            }
      }

      vector<pair<ll, ll>> d(n);
      for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                  if (g[i][j] != a[i] && g[i][j] != 1) {
                        d[i].first = a[i]/g[i][j];
                        d[i].second = g[i][j];
                        break;
                  }
            }

            if (d[i].first) continue;

            for (auto u: div) {
                  if (a[i] % u.first == 0) {
                        d[i].first = a[i]/u.first;
                        d[i].second = u.first;
                  }
            }
      }

      map<ll, ll> surplus;
      for (int i = 0; i < n; i++) {
            if (d[i].first == 0) {
                  surplus[a[i]]++;
            } else {
                  div[d[i].first]++;
                  div[d[i].second]++;
            }
      }

      ll ans = 1;
      ll M = 998244353;
      for (auto u: div) {
            ans *= (u.second+1);
            ans %= M;
      }

      for (auto u: surplus) {
            ans *= (u.second+1);
            ans *= (u.second+1);
            ans %= M;
      }
      cout << ans;

	return 0;
}
