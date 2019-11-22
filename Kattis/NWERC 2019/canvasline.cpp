#include <bits/stdc++.h>
using namespace std;

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	int n; cin >> n;
	vector<int> l(n), r(n);
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
	}
	set<int> pegs;
	vector<int> cnt(n);
	int p; cin >> p;
	for (int i = 0; i < p; i++) {
		int x; cin >> x;
		pegs.insert(x);
		for (int j = 0; j < n; j++) {
			if (l[j] <= x && r[j] >= x) {
				cnt[j]++;
			}
		}
	}

	vector<int> ans;
	for (int i = 0; i < n; i++) {
		if (cnt[i] > 2) {
			cout << "impossible"; exit(0);
		}
		// if 0 peg, place one on the leftmost+1
		// if 1 peg, place one of the rightmost if possible
		// need to check the next

		if (cnt[i] == 0) {
			ans.push_back(l[i]+1);
			pegs.insert(l[i]+1);
			cnt[i]++;
		}

		if (cnt[i] == 1) {
			// if there is no canvas to the right, place on rightmost possible
			if (i == n-1) {
				for (int j = r[i]; j >= l[i]; j--) {
					if (pegs.find(j) == pegs.end()) {
						pegs.insert(j);
						ans.push_back(j);
						cnt[i]++;
						break;
					}
				}
			} else {
				// if it is adjacent to the next one
				// place on rightmost if possible
				if (r[i] == l[i+1]) {
					// place on r[i]
					if (pegs.find(r[i]) == pegs.end() && cnt[i+1] < 2) {
						pegs.insert(r[i]);
						ans.push_back(r[i]);
						cnt[i+1]++; cnt[i]++;
					} else {
						for (int j = r[i]-1; j >= l[i]; j--) {
							if (pegs.find(j) == pegs.end()) {
								pegs.insert(j);
								ans.push_back(j);
								cnt[i]++;
								break;
							}
						}
					}
				} else {
					for (int j = r[i]; j >= l[i]; j--) {
						if (pegs.find(j) == pegs.end()) {
							pegs.insert(j);
							ans.push_back(j);
							cnt[i]++;
							break;
						}
					}
				}
			}
		}
	}
	cout << ans.size() << '\n';
	for (int i: ans) cout << i << ' ';

	return 0;
}