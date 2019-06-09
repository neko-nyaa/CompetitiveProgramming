/*
	https://community.topcoder.com/stat?c=problem_statement&pm=11929&rd=14734

	- The expected place of a word is the expected number of words that it will beat
	- By linearty of expectation, is it also the sum of probability that this word beats other words.

	- So our solution is actually super simple. For each word in our list:
		+ Find the probablity that it beats each of the other words
		+ Sum all the probability together, we get the expected place of the word.

	- How to find the probability? Let's observe that the comparison of the word depends only on the first different character compared.
	- So it's sufficient to get the probability that the first such pair is in favor of the word considering.
	- Since the number of permutations that have this property is the same for all pairs, it is simply their ratio.
	- In other words, it's simply count(pairs with words[i][k] > words[j][k])/count(pairs with words[i][k] != words[j][k])

*/

#include <bits/stdc++.h>
using namespace std;

class StrangeDictionary{
public:
	vector<double> getExpectedPositions(vector<string> words) {
		vector<double> ans;
		int n = words.size();
		int l = words[0].size();

		for (int i = 0; i < n; i++) {
			double expected_pos = 0;
			for (int j = 0; j < n; j++) {
				if (i == j) continue;

				double p = 0, q = 0;
				for (int k = 0; k < l; k++) {
					if (words[i][k] == words[j][k]) continue;

					q += 1;
					p += (words[i][k] > words[j][k]);
				}
				expected_pos += p/q;
			}
			ans.push_back(expected_pos);
		}

		return ans;
	}
};