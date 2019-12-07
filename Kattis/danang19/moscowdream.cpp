#include <bits/stdc++.h>
using namespace std;
int main() {
	int a, b, c, n; cin >> a >> b >> c >> n;
	if (a == 0 || b == 0 || c == 0) {
		cout << "NO\n"; exit(0);
	}
	if (a+b+c < n) {
		cout << "NO\n"; exit(0);
	}
	if (n < 3) {
		cout << "NO\n"; exit(0);
	}
	cout << "YES\n";
	return 0;
}