/*
	Weighted job scheduling?
*/

#include <bits/stdc++.h>
using namespace std;

struct Job {
	long long start, finish, profit;
};

long long findLastNonConflictingJob(vector<Job> &jobs, long long n) {
	long long low = 0;
	long long high = n;

	while (low <= high) {
		long long mid = (low + high) / 2;
		if (jobs[mid].finish <= jobs[n].start) {
			if (jobs[mid + 1].finish <= jobs[n].start) {
				low = mid + 1;
			} else {
				return mid;
			}
		} else {
			high = mid - 1;
		}
	}

	return -1;
}


long long solve(vector<Job> &jobs) {
	sort(jobs.begin(), jobs.end(), [](Job &x, Job &y) {
		return x.finish < y.finish;
	});

	long long n = jobs.size();

	long long maxProfit[n];
	maxProfit[0] = jobs[0].profit;

	for (long long i = 1; i < n; i++) {
		long long index = findLastNonConflictingJob(jobs, i);
	 
		long long incl = jobs[i].profit;
		if (index != -1) {
			incl += maxProfit[index];
		}

		maxProfit[i] = max(incl, maxProfit[i-1]);
	}

	return maxProfit[n-1];
}

void solve() {
	long long n, m; cin >> n >> m;
	vector<Job> a;
	while (m--) {
		long long t, x, y, z; cin >> t >> x >> y >> z;
		a.push_back({x, y, z});
	}
	cout << solve(a) << '\n';
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