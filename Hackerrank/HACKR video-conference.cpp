/*
      https://www.hackerrank.com/contests/hourrank-30/challenges/video-conference

      - A little trie modification will pass this. Good problem for trie practice, but not interesting overall.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
      string tmp, ans;
      for (int i = 0; i < n; i++) {
            int ch = s[i] - 'a';
            tmp += s[i];
            if (p->child[ch] == nullptr) {
                        if (ans.size() == 0) ans = tmp;
                  p->child[ch] = new trie();
            }
            p = p->child[ch];
      }
      p->cnt++;

      if (ans.size() == 0) ans = tmp;
      cout << ans << " ";
      if (p->cnt > 1) cout << p->cnt;
      cout << '\n';
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      int n; cin >> n;
      while (n--) {
            string s; cin >> s;
            insert(s);
      }

      return 0;
}

