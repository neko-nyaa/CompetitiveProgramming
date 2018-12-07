/*
	https://hanoi18.kattis.com/problems/hanoi18.grabagraph

      - Without loss of generality, let's assume our source node is 1, and our destination is N (chosen by us).
      We can just swap N and 2 when we output.

      - Let's solve the following problem first: "Given graph, find A (count shortest paths)."
      This can be easily solved with DP. We can model the shortest-path graph as a DAG. 
      Our recurrence is now dp[node] = sum of all (dp[parents]).

      - In fact, since we can put weights on edges, we can fine-tune the weight to our needs. So this is just counting normal paths.

      - Let's get to the actual problem. We have two graphs to be built. Let's solve them separately.

---------------------------------------------- GRAPH 1: 72 NODES, 2525 EDGES ----------------------------------------------------------
      
      - Let's build a 62-clique, with the weight of edge (i, j) be |i - j|. Now every paths from 1 to any other node is the shortest.
      The path count from 1 each node reduces to ordered partition problem: https://en.wikipedia.org/wiki/Partition_(number_theory)
      The length of path from 1 to N is |N - 1|, so answer is 2^(length - 1) = 2^(N-2).

      - Now we have all the values of 2^i with i from 0 to 60. We also have our recurrence dp[node] = sum of all (dp[parents])
      We just have to choose some "parents" to sum up to dp[destination]. Use the binary representation of A to construct the sum.

      - So in fact, 63 nodes and around 2013 edges are enough.

---------------------------------------------- GRAPH 2: 88 NODES, 214 EDGES ----------------------------------------------------------

      - We have much less edges now. We now only have 2.43 edges per node. Let's see what recurrence can we come up with.

      - There is a powerful sequence for this: dp[i] = dp[i-1] + dp[i-2]. Yes, it is the fibonacci sequence.
      If we weight the edges in the same manner as the previous graph, we can obtain all values from F(1) to F(87) using 87 nodes and 171 edges.
      And it turns out that F(88) is the first value that exceeds our contrain, so we have just enough nodes for this.

      - Now we just have to sum some F() up to A. By Zeckendorf's theorem, we can greedily pick the largest F() every time.
      So we just do things in the same manner as graph 1.

      - In total, we will need all 88 nodes and around 200 edges for this. 
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> fib = {0, 1};

void init() {
      for (int i = 2; i < 88; i++) {
            fib.push_back(fib[i-1] + fib[i-2]);
      }
}

void solve1(int n) {
      cout << "YES\n";

      // build a clique
      vector<tuple<int, int, int>> ans;
      for (int i = 1; i <= 62; i++) {
            for (int j = i+1; j <= 62; j++) {
                  ans.emplace_back(i, j, j-i);
            }
      }

      // connect certain nodes to sink
      for (int i = 0; i <= 60; i++) {
            if (n & (1LL << i)) {
                  int w = 63 - (i+2);
                  int e = i+2;

                  ans.emplace_back(63, e, w);
            }
      }

      // output
      cout << "63 " << ans.size() << '\n';
      for (auto [x, y, z]: ans) {
            if (x == 63) {x = 2;}
            else if (x == 2) {x = 63;}

            if (y == 63) {y = 2;}
            else if (y == 2) {y = 63;}

            cout << x << ' ' << y << ' ' << z << '\n';
      }
}

void solve2(int n) {
      cout << "YES\n";

      // build a fibonacci graph
      vector<tuple<int, int, int>> ans;
      for (int i = 2; i <= 87; i++) {
            ans.emplace_back(i-1, i, 1);
            if (i == 2) continue;
            ans.emplace_back(i-2, i, 2);
      }

      // connect certain nodes to sink
      for (int i = 87; i > 0; i--) {
            if (n >= fib[i]) {
                  n -= fib[i];

                  ans.emplace_back(88, i, 88 - i);
            }
      }

      // output
      cout << "88 " << ans.size() << '\n';
      for (auto [x, y, z]: ans) {
            if (x == 88) {x = 2;}
            else if (x == 2) {x = 88;}

            if (y == 88) {y = 2;}
            else if (y == 2) {y = 88;}

            cout << x << ' ' << y << ' ' << z << '\n';
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);
      init();

      int n;
      while (cin >> n) {
            if (n == -1) return 0;
            solve1(n);
            solve2(n);
      }

      return 0;
}