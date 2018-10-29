/*
      https://codeforces.com/contest/1043/problem/C

      - It's important to notice that our string is binary. This makes the problem tremendously easier.

      - We know that to make our string minimal, we want to put as many 'A'-s as possible into our prefix. Let's see how much A we can put.

      - Let's consider a few cases:
            + Our string is "BBBBB-AAAAAA-BBBBB". It's clear we should flip the smallest prefix with all As.
            + Our string is something like "BBB-A-B-AAA".  If we can somehow get these two A clusters together, then we reach case 1.

      - Let's solve the second case. Can we bring them closer together? Yes we can. This is how we will do it
            + "BBB-A-B-AAA" ---> "A-BBB-B-AAA"
                   |
               Flip here
            + "A-BBBB-AAA" ----> "BBBB-A-AAA"
                    |
                Flip here
            + Then we flip the entire string and we have the absolute minimal.

      - Now we know how to bring every separate clusters of "A" together, we have to merge them all into 1.

      - The implementation is incredibly simple as well, we just have to flip all i-prefixes, such that S[i] != S[i+1]
      Don't forget to flip the entire string too, if the last character is A, so as to bring it back to the top.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      string s; cin >> s;
      int n = s.size();
      vector<int> ans(n);
      for (int i = 0; i < n-1; i++) {
            if (s[i] != s[i+1]) {
                  ans[i] = 1;
            }
      }
      if (s[n-1] == 'a') ans[n-1] = 1;
      for (int i: ans) cout << i << ' ';

      return 0;
}
