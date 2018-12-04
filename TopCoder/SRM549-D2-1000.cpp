/*
	https://community.topcoder.com/stat?c=problem_statement&pm=11955
	- Editorial: https://apps.topcoder.com/wiki/display/tc/SRM+549
	
	- We will rephrase the problem as follow: given a graph with directed edges. Count minimum edges to remove,
	so that graph has no cycles, meaning it has a valid topological ordering.

	- Let's think about a brute force solution. Given a topological ordering, what is the minimum edges to remove, so that it's valid.
	This is easy, the cost is just the number of edges that are in the wrong direction (backwards or self-loops).

	- We have obtained an O(N!) solution. Now to improve it, we will use bitmask DP. With this, we can iterate over subset of nodes,
	instead of permutations of nodes. Laaksonen's CP handbook (1.10.5) is a good read.
	- Link to book: https://cses.fi/book/index.html

	- Let dp[mask] be the minimum cost of the node subset represented by mask. Each mask will have n bits, so they can represent a subset.
	The answer will be in dp[2^n - 1], which is the complete set of nodes.

	- I like to think of this as instead of DP over simple parameters, we will DP over all the subsets.
	If we can understand this, then this problem is very much like a simple knapsack.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class OrderOfTheHats{
public:
	int n;
	int dp[1050000];

	int minChanged(vector<string> spellChart) {
		n = spellChart.size();

		memset(dp, 800, sizeof(dp));
		dp[0] = 0;

		for (int mask = 1; mask < (1 << n); mask++) {
			for (int j = 0; j < n; j++) {
				if (mask & (1 << j)) {
					int cost = 0;

					for (int k = 0; k < n; k++) {
						if (mask & (1 << k)) {
							cost += (spellChart[j][k] == 'Y');
						}
					}

					dp[mask] = min(dp[mask], dp[mask ^ (1 << j)] + cost);
				}
			}
		} 

		return dp[(1 << n) - 1];
	}
};