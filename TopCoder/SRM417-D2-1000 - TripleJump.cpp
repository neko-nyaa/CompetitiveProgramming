/*
	Editorial: https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm417

	- My approach is slightly different from the author's, but they're based on the same thing.

	- Let's reduce the problem first. We will answer the question: "what is the probability that we beat the i-th opponent" 
	Suppose we can jump in range [LOW; HIGH], this also means we can jump in range [0; HIGH - LOW] with a LOW bonus for each jump.
	This means we can subtract (FIRST + LOW*2) from each opponent, and solve the following question instead:
		
		"We pick two jumps (real numbers) uniformly randomly from 0 to N. What is the probability that their sum is >= K".
	
	- In fact, we can change "0 to N" to "0 to 1", "K" to "K/N", and we still have the same question. Let's solve this question instead.

	------------------------------------------------------------------------------------------------------------------------------

	- From here on there can be many ways to solve this problem. The editorial describes something called "Cumulative distribution function"
	Reference: https://en.wikipedia.org/wiki/Cumulative_distribution_function
	Mine is a little different.

	- I used the Irwin-Hall distribution for 2 independent variables. The Irwin-Hall distribution is a distribution for the sum of 
	N random variables in the range [0, 1]. For N = 2, f(x) follows a triangular distribution:
		+ f(x) = x for (0 <= x <= 1)
		+ f(x) = 2-x for (1 <= x <= 2)
	- To find the cumulative sum for f(x) from 0 to K, we simply find the integral of this function bounded by 0 and K.

	Reference: https://en.wikipedia.org/wiki/Irwin%E2%80%93Hall_distribution

	------------------------------------------------------------------------------------------------------------------------------

	- We have effectively solved this problem. The probability of getting exactly i-th place is simply:
		P(exactly i-th place) = P(place i or higher) - P(place i+1 or higher)
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class TripleJump{
public:
	double calc(double n, double k) {
		// what is the probability that we get to >= k in 2 jumps
		// assuming our jump is [0, n]
		if (k <= 0) return 1;
		if (k >= 2*n) return 0;

		double x = k/n;

		if (x > 1) {
			return x*x/2 - 2*x + 2;
		} else {
			return 1 - x*x/2;
		}
	}

	vector<double> getProbabilities(int lower, int upper, int first, vector<int> opponents) {
		for (int &i: opponents) {
			i -= first + lower*2;
		}
		upper -= lower;

		sort(opponents.begin(), opponents.end(), greater<int>());
		opponents.push_back(0);

		vector<double> ans;
		double prev = 0;

		for (int i: opponents) {
			double prob = calc(upper, i);

			ans.push_back(prob - prev);
			prev = prob;
		}

		return ans;
	}
};