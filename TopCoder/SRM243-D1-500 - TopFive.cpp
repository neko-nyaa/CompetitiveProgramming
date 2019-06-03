/*
	https://community.topcoder.com/stat?c=problem_statement&pm=4453&rd=7218

	- For each opponent contestant, we want to answer this question:
		"What is the probability that this contestant beats us?"
	  Since there are only 3 problems, we can iterate through all subset of problems, 
	  and find the probability that this opponent gets this subset correct

	- We want to make top 5, this means we want no more than 4 contestants to beat us.
	  We have nCr(50, 4) ~ 230000. This means we can just brute force and find any <= 4 contestants that will beat us.
*/

#include <bits/stdc++.h>
using namespace std;

class TopFive{
public:
	double calc(string r, string a, int pts) {
		// probability that we beat this contestant
		stringstream res, acc;
		res << r; acc << a;

		vector<double> ac(3);
		vector<int> rs(3);
		for (int i = 0; i < 3; i++) {
			res >> rs[i];
			int x; acc >> x;
			ac[i] = x*1.0/100;
		}

		double ans = 0;
		for (int mask = 0; mask < 8; mask++) {
			double p = 1;
			int score = 0;
			for (int i = 0; i < 3; i++) {
				if (mask & (1 << i)) {
					score += rs[i];
					p *= ac[i];
				} else {
					p *= (1 - ac[i]);
				}
			}
			if (score < pts) {
				ans += p;
			}
		}

		return ans;
	}

	void brute(int i, int cnt, vector<double> &proba, double &ans, double cur) {
		if (cnt >= 5) return;
		if (i == proba.size()) {
			ans += cur;
		} else {
			// i-th contestant beats us
			brute(i+1, cnt+1, proba, ans, cur*(1 - proba[i]));
			// i-th contestant loses to us
			brute(i+1, cnt, proba, ans, cur*proba[i]);
		}
	}

	double findProbability(vector<string> results, vector<string> accuracies, int points) {
		int n = results.size();

		vector<double> proba;
		for (int i = 0; i < n; i++) {
			proba.push_back(calc(results[i], accuracies[i], points));
		}

		double ans = 0;
		brute(0, 0, proba, ans, 1);
		return ans;
	}
};