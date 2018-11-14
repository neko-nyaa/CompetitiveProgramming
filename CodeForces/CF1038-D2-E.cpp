/*
      https://codeforces.com/contest/1038/problem/E

      - We are given an array of weighted domino pieces of ONLY 4 COLORS. Find the max weight valid domino sequence we can make.
      This was one of the problems I couldn't solve before. It seem very interesting now.

      - We can convert the problem as follow: given a graph with 4 nodes, and a lot of weighted edges. Find the max weight path we can make
      without visiting the same edge twice.

      - Sound like Euler Path. The hardest part is probably to determine how many edges we can actually visit.
      To answer this question, let's make a few observations:

      - Assume a connected graph, an Euler Path exists if and only if the number of odd-degree nodes in the graph is 0 or 2.
            + Our graph only has 4 nodes. Therefore the number of odd-degree nodes has to be 0, 2, or 4.
            + If our graph isn't connected, then there are no components with 4 nodes. Therefore each CC must have euler path.
            + We have only 4 colors, so we can have at most 10 different types of dominoes.

      - These info are enough for us to think of a brute-force solution. Let's try to construct one such solution:
            + If our graph is disconnected, answer for a connected component is simply sum of all edges of that component. Take the maximum of those answers.
            + If our graph is connected, there are 2 cases:
                  * The number of odd-degree nodes is 0 or 2. In this case Euler Path exists, take the sum of all edges.
                  * The number of odd-degree nodes is 4. We can remove any edge that's NOT a self-loop. Now Euler Path must exists.

      - To sum up: If Euler Path exists, take sum of all edges. If Euler Path does not exist, remove one edge, solve the problem again.
      Be careful, if we remove an edge, the graph might become disconnected. Don't forget to handle this.

      - This can be O(N^2) if we try to remove each edge, or O(N) if we try to remove edges smartly (removing minimum of each distinct type of domino)
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> P, S;
	DSU(int n) {
		P.resize(n+1);
		S.resize(n+1, 1);
		for (int i = 1; i <= n; i++) P[i] = i;
	}

	void reset() {
		for (int i = 1; i <= P.size(); i++) P[i] = i, S[i] = 1;
	}

	int find(int x) {
		while (x != P[x]) x = P[x];
		return x;
	}

	void merge(int a, int b) {
		a = find(a); b = find(b);
		if (S[a] < S[b]) swap(a, b);

		S[a] += S[b];
		P[b] = a;
	}

	int same(int a, int b) {
		return find(a) == find(b);
	}
};

int n;
DSU d(4);
int deg[5];
int ans[5];
int x[101], y[101], w[101];

int output(int ind) {
      memset(ans, 0, sizeof(ans));
      for (int i = 0; i < n; i++) {
            if (i == ind) continue;
            ans[d.find(x[i])] += w[i];
      }
      return *max_element(ans, ans + 5);
}

int solve(int a, int b) {
      d.reset(); int ind = -1;
      for (int i = 0; i < n; i++) {
            if (x[i] == a && y[i] == b) {
                  if (ind == -1 || w[i] < w[ind]) ind = i;
            }
      }
      if (ind == -1) return 0;

      for (int i = 0; i < n; i++) {
            if (i == ind) continue;
            if (!d.same(x[i], y[i])) {d.merge(x[i], y[i]);}
      }
      return output(ind);
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> n;
      int cc = 4;
      for (int i = 0; i < n; i++) {
            cin >> x[i] >> w[i] >> y[i];
            if (x[i] > y[i]) swap(x[i], y[i]);
            if (!d.same(x[i], y[i])) {d.merge(x[i], y[i]); cc--;}
            deg[x[i]]++; deg[y[i]]++;
      }

      int c = 0;
      for (int i = 1; i <= 4; i++) {
            c += deg[i] % 2;
      }

      if (c == 4 && cc == 1) {
            int answer = 0;
            for (int i = 1; i <= 4; i++) {
                  for (int j = 1; j < i; j++) {
                        answer = max(answer, solve(j, i));
                  }
            }
            cout << answer;
      } else {
            cout << output(-1);
      }

      return 0;
}
