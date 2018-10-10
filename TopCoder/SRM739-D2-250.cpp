/*
      https://community.topcoder.com/stat?c=problem_statement&pm=15099&rd=17298&rm=331762&cr=40629265

      - Given cow positions c[] and barn positions b[], we need to find the smallest distance from each cow to a barn.
      Prioritize smaller barn positions.

      - Constrains are low, so this can be brute-forced.

      - For each cow, we will iterate through the barns, finding the barn with the smallest distance.

      - Be careful of constrains, neither arrays are sorted initially.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class HungryCowsEasy{
public:
	vector<int> findFood(vector<int> c, vector<int> b) {
		int n = c.size();
		int m = b.size();
		vector<int> anss(n);

		for (int i = 0; i < n; i++) {
			int ans = 0;
			for (int j = 1; j < m; j++) {
				if (abs(c[i] - b[j]) < abs(c[i] - b[ans])) {
					ans = j;
				} else if (abs(c[i] - b[j]) == abs(c[i] - b[ans])) {
					if (b[j] < b[ans]) ans = j;
				}
			}
			anss[i] = ans;
		}

		return anss;
	}
};
