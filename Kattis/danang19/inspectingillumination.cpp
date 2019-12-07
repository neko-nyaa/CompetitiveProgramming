/*
	Author: Nhat Chung
*/

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

typedef pair <int, int> ii;
int ask(vector <ii> &ranges) {
	vector <int> stuff;
	for (auto &e : ranges) {
		int l = e.first, r = e.second;
		int m = (l + r)/2;
		for (int i = l; i <= m; i++)
			stuff.push_back(i);
	}
	cout << "ASK " << stuff.size();
	for (int i = 0; i < stuff.size(); i++)
		cout << " " << stuff[i];
	cout << '\n' << flush;

	return stuff.size();
}

void separate(vector <ii> &ranges, vector <vector <int>> &group, map <int, int> &M) {
	vector <ii> new_ranges;
	vector <vector <int>> new_group;

	int g = ranges.size();
	for (int i = 0; i < g; i++) {
		auto e = ranges[i];
		int l = e.first, r = e.second;
		if (l == r) {
			new_ranges.push_back({l, r});
			new_group.push_back(group[i]);
		}
		else {
			int m = (l + r)/2;
			new_ranges.push_back({l, m});
			new_ranges.push_back({m + 1, r});
			vector <int> g1, g2;
			for (int color : group[i]) {
				if (M[color] != 0)
					g1.push_back(color);
				else
					g2.push_back(color);
			}
			new_group.push_back(g1);
			new_group.push_back(g2);
		}
	}

	ranges = new_ranges;
	group = new_group;
}

void solve() {
	int n; cin >> n;
	vector <ii> ranges(1, {1, n});
	vector <vector <int>> group(1);
	for (int i = 1; i <= n; i++) {
		group[0].push_back(i);
	}

	while (true) {
		int num = ask(ranges);

		map <int, int> M;
		for (int i = 0; i < num; i++) {
			int x; cin >> x;
			M[x] = 1;
		}

		separate(ranges, group, M);

		if (group.size() == n)
			break;
	}

	cout << "ANSWER";
	map <int, int> A;
	for (int i = 0; i < n; i++)
		A[group[i][0]] = i+1;
	for (auto &e : A)
		cout << ' ' << e.second;
	cout << '\n' << flush;
} //*/

int main() {
	ios_base::sync_with_stdio(0);

	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}