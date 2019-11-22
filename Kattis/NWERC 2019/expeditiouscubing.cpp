// Author: Nhat Chung

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

int main() {
	ios_base::sync_with_stdio(0);
	
	vector <double> a;
	for (int i = 0; i < 4; i++) {
		double x; cin >> x;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
	
	double target; cin >> target;
	target *= 3;
	
	double sum = 0.0;
	for (int i = 1; i < 4; i++)
		sum += a[i];
	
	if (sum - target < eps) {
		cout << "infinite\n";
		return 0;
	}
	
	sum -= a[3];
	double tmp_answer = target - sum;
	
	if (tmp_answer - a[0] < -eps) {
		cout << "impossible\n";
		return 0;
	}
	
	cout << fixed << setprecision(2) << tmp_answer << '\n';
	return 0;
}
