/*
	- Okay so we need to find for each string, how many strings are there with edit distance of 1 from this.

	- To be noticed: length of each word is <= 10
	  So we have like, suppose word of length K
	  Then <= K words of length K-1, 25*K words of length K, ~25*(K+1) words of length K+1
	  Which is ~500 strings in worst case
	
	- Let's build a trie out of these N input words. 
	  To find similarity of each word, generate every possible edit words with recursion.
	  Then follow the link in the trie.

	- But, we have to generate words smartly as well.
	  If we generate words naively, then one word may appear multiple times.
*/

#include <bits/stdc++.h>
using namespace std;

struct trie{
	trie* child[26];
	int cnt;
	trie() {
		for (int i = 0; i < 26; i++) {
			child[i] = nullptr;
		}
		cnt = 0;
	}
};

trie *t = new trie();

void insert(string s) {
	int n = s.size();

	trie *p = t;
	for (int i = 0; i < n; i++) {
		int ch = s[i] - 'a';
		if (p->child[ch] == nullptr) {
			p->child[ch] = new trie();
		}
		p = p->child[ch];
	}
	p->cnt = 1;
}

int n;
int similarity[50000];

void generate(string &s, int i, int edited, int &id, int len, trie* j) {
	if (j == NULL) return;
	if (i >= s.size()) {
		if (edited) {
			similarity[id] += (j->cnt);
		} else {
			// if not edited, then the only choice left is to insert character into last position
			if (i == s.size()) {
				for (char c = 'a'; c <= 'z'; c++) {
					generate(s, i+1, 1, id, len+1, j->child[c - 'a']);
				}
			}
		}
	} else {
		if (edited) {
			generate(s, i+1, 1, id, len+1, j->child[s[i] - 'a']);
		} else {
			// not editing at this
			generate(s, i+1, 0, id, len+1, j->child[s[i] - 'a']);

			// editing at this
			// 1. delet: can only delete if i == 0 or s[i] != s[i-1]
			if (i == 0 || s[i] != s[i-1]) {
				generate(s, i+1, 1, id, len, j);
			}
			// 2. insert: can insert character c if s[i] != c
			// inserts c to before position i
			for (char c = 'a'; c <= 'z'; c++) {
				if (s[i] != c) {
					generate(s, i, 1, id, len+1, j->child[c - 'a']);
				}
			}
			// 3. modify
			for (char c = 'a'; c <= 'z'; c++) {
				if (s[i] != c) {
					generate(s, i+1, 1, id, len+1, j->child[c - 'a']);
				}
			}
		}
	}
}

void calc_similarity(string &s, int id) {
	generate(s, 0, 0, id, 0, t);
}

void solve() {
	t = new trie();

	cin >> n;
	vector<string> s(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		similarity[i] = 0;
		insert(s[i]);
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		calc_similarity(s[i], i);
		ans = max(ans, similarity[i]);
	}

	for (int i = 0; i < n; i++) {
		if (similarity[i] == ans) {
			cout << s[i] << '\n';
			return;
		}
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int t; cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
	
	return 0;
}