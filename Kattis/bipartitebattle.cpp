/*
	https://hanoi18.kattis.com/problems/hanoi18.bipartitebattle

      - The key idea is here: https://people.eecs.berkeley.edu/~vitchyr/chomp_the_graph.pdf

      - The player can only win if the initial graph only has even edges and even vertices count.
      So problem reduces to "if sum of vertices is odd, output 0. Else output number of ways to draw even number of edges".

      - In each graph, there are at most a*b edges. So there are 2^(a*b) ways to draw edges. Half of them have even edge count.

      - Our final answer is 2^(sum of all a*b)/2. 
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int M = 1e9+7;

int modpow(int n, int k) {
      if (k == 0) return 1;

      int tmp = modpow(n, k/2);
      tmp = (tmp*tmp) % M;

      if (k % 2) return (tmp*n) % M;
      return tmp;
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int t; cin >> t;
      int prod = -1, par = 0;
      while (t--) {
            int a, b; cin >> a >> b;
            par ^= (a+b) & 1;
            prod = (prod + a*b) % (M-1);
      }
      if (par) cout << 0;
      else cout << modpow(2, prod);

      return 0;
}
