/*
	https://hanoi18.kattis.com/problems/hanoi18.lazylearner

	- Suppose we have a substring [l, r] and a word W. It is easy to check in linear time if W is a subsequence of [l, r] or not.

	- We will solve this problem in offline. Sort all the words and the queries in lexicographical order.
	Now, we will divide the queries into 500 batches, with the i-th batch containing queries starting at S[i].

	- Solve the problem 500 times, with each time starting at S[i], answering the i-th query batch.
	Let's keep N pointers, each corresponding to a word. Each time we move ahead one character, we will move all the corresponding pointers. 

	- If a pointer moves to the end of the word, that word is now a subsequence, and we will push it in our list of "for answering".

	- To answer queries in solve time, we will need online k-th order statistics. A treap or PBDS will work.

	- See implementation for better understanding.
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int n, q;
string s;
vector<string> t;
vector<int> ans(300001, -1);
vector<tuple<int, int, int>> que[501];

void solve(int start) {
      vector<int> ptr(n);
      vector<int> bucket[26];
      for (int i = 0; i < n; i++) {
            int a = t[i][0] - 'a';
            bucket[a].push_back(i);
      }

      int petr = start;

      indexed_set<int> st;

      for (auto [r, k, i]: que[start]) {
            for (; petr <= r; petr++) {
                  int c = s[petr] - 'a';

                  vector<int> tmp = bucket[c];
                  bucket[c].clear();
                  for (auto u: tmp) {
                        ptr[u]++;

                        if (ptr[u] == t[u].size()) st.insert(u);
                        else {
                              int a = t[u][ptr[u]] - 'a';
                              bucket[a].push_back(u);
                        }
                  }
            }

            if (k < st.size()) {ans[i] = *st.find_by_order(k);}
      }
}

signed main() {
      ios::sync_with_stdio(0); cin.tie(0);

      cin >> s >> n >> q;
      for (int i = 0; i < n; i++) {
            string x; cin >> x;
            t.push_back(x);
      }
      sort(t.begin(), t.end());
      for (int i = 0; i < q; i++) {
            int l, r, k; cin >> l >> r >> k; l--; r--; k--;
            que[l].emplace_back(r, k, i);
      }
      for (int i = 0; i < s.size(); i++) {
            sort(que[i].begin(), que[i].end());
      }

      for (int i = 0; i < s.size(); i++) {
            solve(i);
      }

      for (int i = 0; i < q; i++) {
            if (ans[i] == -1) {cout << "NO SUCH WORD\n";}
            else {
                  int ss = ans[i];
                  for (int j = 0; j < min(10, (int)t[ss].size()); j++) {
                        cout << t[ss][j];
                  }
                  cout << '\n';
            }
      }
}
