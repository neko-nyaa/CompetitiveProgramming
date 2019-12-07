/*
	Please do not look at the code. It is ugly and is mostly copy-pasted if-elses.

	- Let's try a simple solution: we build up the "sorted" array one by one.
		+ An array of size 2 is always sorted. We can start with a subarray of size 2, then try to add numbers one by one.
		+ If our array is [(2, 1), 3], we can reverse (2, 1), and the sorted part will be [(1, 2, 3)]. This takes one operation.
		+ If the number is somehow in the middle, say [(1, 2, 4, 5), 3], we can do:
			[1, 2, 4, 5, 3] -> [1, 2, (5, 4), 3] -> [1, 2, (3, 4, 5)]
		  This takes 2 operations.
		+ If after adding all numbers, the array is in reverse order, we need to reverse it once. This takes one operation.
	- Let's analyze how well it does:
		+ There are 2 numbers from the start, so we need to add N-2 more.
		+ Each addition takes at most 2 operations, except the first one takes 1.
		+ We may need to reverse at the end.
	  So it takes at most 2*(N-2) <= 196. We have 191 operations.

	- Let's analyze a little better: the worst case only happens when we need to insert into the middle of our sorted part. We just need to avoid this worst case.
	If we cherry-pick our starting subarray (for example, by value as close to the middle as possible), then it will be very hard to design tricky test cases for this (it might be impossible to!)

	- And, let's do better, since there are only N-1 <= 99 possible starting subarrays, we can try all of them and pick any answer we want!
	191 operations is so lenient you can pick one random subarray and still get away with an AC.
*/

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define try jewapjo

vector<pair<int, int>> try(vector<int> &a, int n, int l, int r) {
	vector<int> b = a;
	vector<pair<int, int>> ans;

	for (int i = l-1; i >= 0; i--) {
		// add a[i] into this sorted array
		if (b[l] < b[r]) {
			// sorted ascending
			if (b[i] < b[l]) {
				l = i; continue;
			}

			if (b[i] > b[r]) {
				ans.emplace_back(l, r);
				reverse(b.begin()+l, b.begin()+r+1);
				l = i;
				continue;
			}

			for (int j = l; j <= r; j++) {
				if (b[j] > b[i]) {
					if (l != j-1) {
						ans.emplace_back(l, j-1);
						reverse(b.begin()+l, b.begin()+j);
					}

					l = i;
					ans.emplace_back(l, j-1);
					reverse(b.begin()+l, b.begin()+j);
					break;
				}
			}
		} else {
			// sorted descending
			if (b[i] > b[l]) {
				l = i; continue;
			}

			if (b[i] < b[r]) {
				ans.emplace_back(l, r);
				reverse(b.begin()+l, b.begin()+r+1);
				l = i;
				continue;
			}

			for (int j = l; j <= r; j++) {
				if (b[j] < b[i]) {
					if (l != j-1) {
						ans.emplace_back(l, j-1);
						reverse(b.begin()+l, b.begin()+j);
					}
					l = i;
					ans.emplace_back(l, j-1);
					reverse(b.begin()+l, b.begin()+j);
					break;
				}
			}
		}
	}

	for (int i = r+1; i < n; i++) {
		// add a[i] into sorted array
		if (b[l] < b[r]) {
			// sorted ascending
			if (b[i] > b[r]) {
				r = i; continue;
			}

			if (b[i] < b[l]) {
				ans.emplace_back(l, r);
				reverse(b.begin()+l, b.begin()+r+1);
				r = i;
				continue;
			}

			for (int j = r; j >= l; j--) {
				if (b[j] < b[i]) {
					j++;
					if (j != r) {
						ans.emplace_back(j, r);
						reverse(b.begin()+j, b.begin()+r+1);
					}

					r = i;
					ans.emplace_back(j, r);
					reverse(b.begin()+j, b.begin()+r+1);
					break;
				}
			}
		} else {
			// sorted descending
			if (b[i] < b[r]) {
				r = i; continue;
			}

			if (b[i] > b[l]) {
				ans.emplace_back(l, r);
				reverse(b.begin()+l, b.begin()+r+1);
				r = i;
				continue;
			}

			for (int j = r; j >= l; j--) {
				if (b[j] > b[i]) {
					j++;
					if (j != r) {
						ans.emplace_back(j, r);
						reverse(b.begin()+j, b.begin()+r+1);
					}
					r = i;
					ans.emplace_back(j, r);
					reverse(b.begin()+j, b.begin()+r+1);
					break;
				}
			}
		}
	}
	if (b[0] > b[n-1]) {
		ans.emplace_back(0, n-1);
	}
	return ans;
}

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n == 1) {
		cout << "0\n"; exit(0);
	}

	for (int i = 1; i < n; i++) {
		vector<pair<int, int>> ops = try(a, n, i-1, i);
		if (ops.size() <= 191) {
			cout << ops.size() << '\n';
			for (auto [u, v]: ops) {
				cout << u+1 << ' ' << v+1 << '\n';
			}
			exit(0);
		}
	}
	exit(1);
}

int main() {
	ios_base::sync_with_stdio(0);

	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}