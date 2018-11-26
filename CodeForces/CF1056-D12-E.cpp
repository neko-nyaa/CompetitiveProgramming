/*
      https://codeforces.com/contest/1056/problem/E

      - Editorial: https://codeforces.com/blog/entry/63461
      Editorial explains it well.

      - Without loss of generality, let's assume the first character in T is 0. If it's not, we can just flip the entire string.

      - Define "Z" the count of zeroes in T, and "O" the count of ones in T.
      This gives us an important hint, is that the length of 0-string and 1-string must match the length of S.
      So we have Z*x + O*y = |S|, with x and y being the length of 0-string and 1-string, respectively.

      - Let's iterate on the roots of this linear diophantine equation. That is, the length of the 0-string and 1-string.
      For each root, if we use string hashing, and we know the length of 0-str and 1-str, we can check whether string S matches string T in O(|T|).
      So this gives us a complexity of O(root*|T|)

      - In fact, this is enough. Let's prove that this complexity runs in time.
      There are at most min(|S|/Z, |S|/O) candidates for the root. Worse case scenario happens when Z = O.
      In which case, the number of checks we do is root*|T| = (|S|/Z)*|T| = |S|*Z/2*Z = 2*|S|.

      - So we will do at most 2*|S| checks, and our solution's run time is just O(|S|).
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll M[] = {982451653, 1000000009, 998244353, 1000000007};

string s, t;
int n, ans, fi;
ll hs[4][1000007];
ll power[4][1000007];

void init() {
      for (int j = 0; j < 4; j++) {
            hs[j][0] = t[0];
            for (int i = 1; i <= n; i++) {
                  hs[j][i] = (hs[j][i-1]*256 + t[i]) % M[j];
            }

            power[j][0] = 1;
            for (int i = 1; i <= n; i++) {
                  power[j][i] = power[j][i-1]*256 % M[j];
            }
      }
}

int cmp(int l, int r, int x, int y) {
      int len1 = r-l+1;
      int len2 = y-x+1;
      if (len1 != len2) return 0;
      ll ans1, ans2;
      for (int i = 0; i < 4; i++) {
            ans1 = (hs[i][r] - (hs[i][l-1] * power[i][len1]) % M[i] + M[i]*M[i]) % M[i];
            ans2 = (hs[i][y] - (hs[i][x-1] * power[i][len2]) % M[i] + M[i]*M[i]) % M[i];
            if (ans1 != ans2) return 0;
      }
      return 1;
}

int solve(int a, int b) {
      int la = 0, ra = 0, lb = 0, rb = 0;
      la = 1, ra = a;
      lb = a*fi + 1, rb = a*fi + b;
      if (cmp(la, ra, lb, rb)) return 0;

      int petr = 1;
      for (char c: s) {
            if (c == '0') {
                  if (!cmp(petr, petr+a-1, la, ra)) return 0;
                  petr += a;
            } else {
                  if (!cmp(petr, petr+b-1, lb, rb)) return 0;
                  petr += b;
            }
      }
      return 1;
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

      cin >> s >> t;
      n = t.size();
      t = '#' + t;
      init();

      if (s[0] == '1') {
            for (int i = 0; i < s.size(); i++) {
                  if (s[i] == '0') s[i] = '1';
                  else s[i] = '0';
            }
      }
      for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {fi = i; break;}
      }

      int z = 0, o = 0;
      for (char c: s) {
            if (c == '0') z++;
            else o++;
      }
      //cout << o << ' ' << z << endl;

      for (int i = 1; i*z < n; i++) {
            int k = n - i*z;
            if (k % o) continue;
            //cout << i << ' ' << k/z << endl;

            ans += solve(i, k/o);
      }
      cout << ans;

	return 0;
}
