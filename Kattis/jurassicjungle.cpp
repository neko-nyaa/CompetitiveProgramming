/*
	https://hanoi18.kattis.com/problems/hanoi18.jurassicjungle

      - The answer exists when we can construct either of the following graphs:
            + A cycle of N vertices.
            + A complete graph.
            + A complete bipartite graph.
      - It is easy to see the first case is correct. Let's see why there are no other cases that are correct.

      - Suppose we have a single cycle of size 9 (a nonaagon). Let's add an edge to it, say (3, 7).
      Now we have some nearly-complete hamilton paths. Take an example: 2-1-9-8-7-3-4-5-6. So we have to add edge (2, 6).
      Similarly, we will also have to add edge (1, 5), (2, 6), (3, 7), etc. every chords of that length.

      - Now that we have added some more edges, we have some more nearly-complete paths.
      That's the basic idea, edges add edges until there are no more nearly-complete paths.
*/

#include <bits/stdc++.h>
using namespace std;

void solvebipartite(int n) {
      cout << "YES\n";
      for (int i = 1; i <= n/2; i++) {
            for (int j = n/2+1; j <= n; j++) {
                  cout << i << ' ' << j << '\n';
            }
      }
}

void solvecycle(int n) {
      cout << "YES\n";
      for (int i = 1; i <= n; i++) {
            int j = i+1; if (j == n+1) j = 1;
            cout << min(i, j) << ' ' << max(i, j) << '\n';
      }
}

void solvecomplete(int n) {
      cout << "YES\n";
      for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                  cout << min(i, j) << ' ' << max(i, j) << '\n';
            }
      }
}

void no() {cout << "NO\n";}

void solve(int n, int m) {
      if (n % 2 == 0 && n*n/4 == m) solvebipartite(n);
      else if (n == m) solvecycle(n);
      else if (n*(n-1)/2 == m) solvecomplete(n);
      else no();
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n, m;
      while (cin >> n >> m) {
            if (n == -1) return 0;
            solve(n, m);
      }

      return 0;
}