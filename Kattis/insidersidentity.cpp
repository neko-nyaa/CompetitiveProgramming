/*
	https://open.kattis.com/problems/insidersidentity

	- Before attempting this problem, please solve CSES substrings first. 
	Link: https://cses.fi/problemset/task/1112/
	If you can't solve it then it's probable that you won't understand this one.
	The solution of the CSES problem is also on my github.

	--------------------------------------------------------------------------------------

	- Let's notice that the number of unknown characters is at most 15.
	So we have at most 2^15 = 32768 possible strings. Let's generate all of them :)

	- A trivial DP solution can be easily realized. We can maintain a state for each of these strings.
	But we can't really maintain 32768 parameters in each call, can't we? :(

	- We will use the Aho-Corasick algorithm for this. 
	Useful link: https://cp-algorithms.com/string/aho_corasick.html

	- Let's define dp(i, j, contain) like the CSES problem, but j now is the vertex of the Aho-Corasick trie.
	The transition of j now is simply following the suffix link of the Aho-Corasick trie.

	- Be careful of overflow, use long long!
*/

#include <bits/stdc++.h>
using namespace std;
 
const int K = 2;
 
struct aho_corasick {
 
	struct Vertex {
		int next[K];
		bool leaf = false;
		int p = -1;
		char pch;
		int link = -1;
		int go[K];
 
		Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
			fill(begin(next), end(next), -1);
			fill(begin(go), end(go), -1);
		}
	};
 
	vector<Vertex> t = vector<Vertex>(1);
 
	void add_string(string &s) {
		int v = 0;
		for (char ch : s) {
			int c = ch - '0';
			if (t[v].next[c] == -1) {
				t[v].next[c] = t.size();
				t.emplace_back(v, ch);
			}
			v = t[v].next[c];
		}
		t[v].leaf = true;
	}
 
	int get_link(int v) {
		if (t[v].link == -1) {
			if (v == 0 || t[v].p == 0)
				t[v].link = 0;
			else
				t[v].link = go(get_link(t[v].p), t[v].pch);
		}
		return t[v].link;
	}
 
	int go(int v, char ch) {
		int c = ch - '0';
		if (t[v].go[c] == -1) {
			if (t[v].next[c] != -1)
				t[v].go[c] = t[v].next[c];
			else
				t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
		}
		return t[v].go[c];
	} 
 
	bool is_leaf(int v) {
		return t[v].leaf;
	}
 
} ahcs;
 
int n, m;
string s, t;
 
long long dp[51][1000000][2];
 
void generate(int i) {
	if (i == m) {
		ahcs.add_string(t);
	} else {
		if (s[i] != '*') {
 
			t.push_back(s[i]);
			generate(i+1);
			t.pop_back();
 
		} else {
 
			for (char c = '0'; c <= '1'; c++) {
				t.push_back(c);
				generate(i+1);
				t.pop_back();
			}
 
		}
	}
}
 
long long solve(int i, int j, int contain) {
	if (ahcs.is_leaf(j)) contain = 1;
	if (i == n) return contain;
	if (dp[i][j][contain] != -1) return dp[i][j][contain];
 
	long long ans = 0;
	for (char c = '0'; c <= '1'; c++) {
		ans += solve(i+1, ahcs.go(j, c), contain);
	}
	return dp[i][j][contain] = ans;
}
 
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	cin >> n >> s; m = s.size();
	generate(0);
 
	memset(dp, -1, sizeof(dp));
	cout << solve(0, 0, 0);
 
	return 0;
}