#include <bits/stdc++.h>
using namespace std;

/*
 	Questions to answer
 	- In which weeks does the i-th team score?
 	- At the x-th week, how many teams with <= y points
 	- From the span of weeks [l; r], let w be all weeks in which there is a team get from x to x+1 points
 	  What is sum of w?
*/

#define int long long

struct johnwick_tree{
	int n;
	long long z;
	vector<long long> tree;

	johnwick_tree(int n) {
		this->n = n; z = 0;
		tree.resize(n+1);
	}

	void update(int p, long long val){
		if (p == 0) {z += val; return;}
		for (int i = p; i <= n; i += i & -i) {
			tree[i] += val;
		}
	}
 
	long long sum(int p) {
		if (p == 0) return z;
		long long ans = 0;
		for (int i = p; i; i -= i & -i) {
			ans += tree[i];
		}
		return ans + z;
	}
};

const int MAX = 300002;

int n, w;
vector<int> points[MAX];
vector<int> scoring_weeks[MAX];

vector<int> event[MAX];
vector<long long> event_p[MAX];

vector<long long> ans(MAX, -1);

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 	
	cin >> n >> w;
	for (int i = 1; i <= w; i++) {
		int k; cin >> k;
		while (k--) {
			int x; cin >> x;
			points[i].push_back(x);
		}
	}

// scoring weeks
	for (int i = 1; i <= n; i++) {
		scoring_weeks[i].push_back(0);
	}
	for (int i = 1; i <= w; i++) {
		for (int x: points[i]) {
			scoring_weeks[x].push_back(i);
		}
	}
	for (int i = 1; i <= n; i++) {
		scoring_weeks[i].push_back(w+1);
	}

// prepping events: a team reaches x points at week x
	vector<int> pts(n+1);
	for (int i = 1; i <= w; i++) {
		for (int x: points[i]) {
			pts[x]++;
			event[pts[x]].push_back(i);
		}
	}
// consider all values in event[x] with values in range [L, R]. What is their sum
	for (int i = 1; i <= w; i++) {
		long long cur = 0; event_p[i].push_back(cur);
		for (int x: event[i]) {
			cur += x;
			event_p[i].push_back(cur);
		}
	}

// At the x-th week, how many teams with <= y points
	vector<tuple<int, int, int, int>> evs;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < scoring_weeks[i].size(); j++) {
			int l = scoring_weeks[i][j-1], r = scoring_weeks[i][j] - 1;

			// has exactly j-1 points in weeks [l, r]
			evs.emplace_back(l, r, j-1, i);
		}
	}	
	sort(evs.begin(), evs.end());
	johnwick_tree tr(MAX);

	int petr = 1;
	pts = vector<int>(n+1);
	tr.update(0, n);
	for (auto [l, r, p, team]: evs) {
		// update up to the l-th week
		while (petr <= l) {
			// update the petr-th week
			for (int x: points[petr]) {
				// remove one value of pts[x]
				tr.update(pts[x], -1);
				pts[x]++;
				tr.update(pts[x], 1);
			}
			petr++;
		}

		// at the l-th week, how many teams with <= p points
		int team_cnt = tr.sum(p); 
		int rank = n - team_cnt + 1;

		int tot_rank = rank*(r - l + 1);

		// information about team reaching p+1 points
		int R = upper_bound(event[p+1].begin(), event[p+1].end(), r) - event[p+1].begin();
		int L = lower_bound(event[p+1].begin(), event[p+1].end(), l+1) - event[p+1].begin();
		long long sum = 0;
		if (R != L) {
			sum = event_p[p+1][R] - event_p[p+1][L];
		}
		
		int overthrow = R - L;
		sum -= l*overthrow;	

		tot_rank += (r-l+1)*overthrow - sum;

		ans[team] += tot_rank;
	}

	cout << fixed << setprecision(9);
	for (int i = 1; i <= n; i++) {
		cout << ans[i]*1.0/w << '\n';
	}

	return 0;
}