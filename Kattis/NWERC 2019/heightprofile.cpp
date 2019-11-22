// Author: Nhat Chung

#include <bits/stdc++.h>

using namespace std;

#define double long double
#define int long long
const double eps = 1e-9;

struct line {
	double a, b;
	line(double _a, double _b) : a(_a), b(_b) {}

	bool operator < (line &other) {
		return b < other.b;
	}
};

void update(vector <int> &seg, int node, int start, int end, int l, int r, int val) {
	if (seg[node] != -1) return;
	if (start > r || end < l) return;

	if (l <= start && end <= r) {
		seg[node] = 1;
		if (start == end) {
			seg[node] = val;
			return;
		}
	}

	int mid = (start + end) / 2;
	update(seg, node*2, start, mid, l, r, val);
	update(seg, node*2+1, mid+1, end, l, r, val);
}

int query(vector <int> &seg, int node, int start, int end, int p) {
	if (start == end) return seg[node];

	int mid = (start + end) / 2;
	if (p <= mid) return query(seg, node*2, start, mid, p);
	else		  return query(seg, node*2+1, mid+1, end, p);
}

double getX(double a1, double b1, vector <int> &h, int i, bool from_right = false) {
	double a2 = (h[i] - h[i+1]) / -1000.0;
	double b2 = h[i] + (h[i] - h[i+1]) * i;
	
	// if parallel -> overlapped
	if (abs(a1 - a2) < eps) {
		if (from_right) 
			return (i+1)*1000.0;
		return i*1000.0;    
	}
	
	return (b2 - b1) / (a1 - a2);
}

signed main() {
	int n, k; cin >> n >> k;

	vector <int> h;
	for (int i = 0; i <= n; i++) {
		int hi; cin >> hi;
		h.push_back(hi);
	}

	while (k--) {
		double g; cin >> g;
		g /= 100; 

		vector <double> B;
		for (int i = 0; i <= n; i++) 
			B.push_back(h[i] - g*i*1000);
		
		sort(B.begin(), B.end());
		
		vector <int> left_side(4*(n+1), -1);
		vector <int> right_side(4*(n+1), -1);

		for (int i = 0; i < n; i++) {
			double b1 = h[i] - g*i*1000;
			double b2 = h[i+1] - g*(i+1)*1000;

			double upb = max(b1, b2);
			double dwb = min(b1, b2);

			int start = lower_bound(B.begin(), B.end(), dwb) - B.begin();
			int end = upper_bound(B.begin(), B.end(), upb) - B.begin() - 1;
			update(left_side, 1, 0, n, start, end, i);
		}

		for (int i = n-1; i >= 0; i--) {
			double b1 = h[i] - g*i*1000;
			double b2 = h[i+1] - g*(i+1)*1000;

			double upb = max(b1, b2);
			double dwb = min(b1, b2);
			
			int start = lower_bound(B.begin(), B.end(), dwb) - B.begin();
			int end = upper_bound(B.begin(), B.end(), upb) - B.begin() - 1;
			
			update(right_side, 1, 0, n, start, end, i);
		} 

		double answer = 0;
		
		for (int i = 0; i <= n; i++) {
			// find left point
			int left_bound = query(left_side, 1, 0, n, i);
			double x1 = getX(g, B[i], h, left_bound);
			
			// find right point
			int right_bound = query(right_side, 1, 0, n, i);
			double x2 = getX(g, B[i], h, right_bound, true);
			if (g*n*1000 + B[i] < h[n])
				x2 = n*1000;
			
			answer = max(answer, x2 - x1);
		}
		
		answer /= 1000;
		if (answer < eps)  cout << "impossible\n";
		else 		       cout << fixed << setprecision(9) << answer << '\n';
	}
}
