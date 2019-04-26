/*
	- Consider a function that returns a polynomial f(n, p) = 1^p + 2^p + 3^p + ... + n^p
	- Then it's easy to see the question actually asks for sigma(f(n, i) * c[i])
	- So we can try finding all f(n, p) for p = 0 to 25. Then for each test just input c[i] and calculate result polynomial.
	- Let's find all f(n, p)

	-------------------------------------------------------------------------------

	- It's good to plan first, and think about all what we need to implement. Let's forget about coding for a second.
	- Let's look at the identity at the end of statement:
		(x + 1)^d - x^d = 1 + C(d, 1)*x + C(d, 2)*x^2 + ... + C(d, d-1)*x^(d-1)
	- If we sum up this identity for each x from 1 to n, we get
		(n + 1)^d - 0^d = (1^0 + 2^0 + ... + n^0) + C(d, 1)*(1^1 + 2^1 + 2^2 + ...)
	- This is equivalent to:
		(n + 1)^d = f(n, 0) + C(d, 1)*f(n, 1) + C(d, 2)*f(n, 2) + ... + C(d, d-1)*f(n, d-1)
	- The left hand side can be expanded into a polynomial using binomial coefficient. It helps to initialize a pascal triangle first.
	- The right hand side is a collection of polynomials. If we want to find f(n, d-1), we just move everything else into left hand side.
	- Therefore, we can find f(n, p) sequentially for all p = 0 to 25, using all the previous f(n, p).

	-------------------------------------------------------------------------------

	- Okay we found all f(n, p). Time to code.
	- We will need to implement fractions and polynomials. A polynomial is just an array of fractions.
	- I think, the easiest way we need to implement is (fraction + fraction), (fraction * fraction), (polynomial * fraction), (polynomial + polynomial) 
	- We implement each of these operators, then implement the calculation.
	- After we found all f(n, p), we just take the input, and sum all f(n, i) * c[i], and output our polynomial.
*/

#include <bits/stdc++.h>
using namespace std;

struct fraction{
	long long x, y;

	fraction() {x = 0; y = 1;}
	fraction(long long value) {x = value; y = 1;} 
	fraction(long long x, long long y) {
		if (y < 0) {x *= -1; y *= -1;}

		long long g = abs(__gcd(x, y));
		x /= g; y /= g;
		this->x = x;
		this->y = y;
	} 
};

fraction operator + (fraction a, fraction b) {
	long long g = a.y*b.y/__gcd(a.y, b.y);

	long long da = g / a.y;
	long long db = g / b.y;

	a.x *= da;
	b.x *= db;

	return fraction(a.x + b.x, g);
}

fraction operator * (fraction a, long long c) {
	return fraction(a.x*c, a.y);
}

fraction operator * (fraction a, fraction b) {
	return fraction(a.x*b.x, a.y*b.y);
}

long long nCr[29][29];

struct polynomial{
	vector<fraction> p;

	polynomial(int n) {
		for (int i = 0; i <= n; i++) {
			p.push_back(fraction(nCr[n][i]));
		}
	}

	int degree() {
		return p.size() - 1;
	}
};

polynomial operator +(polynomial a, polynomial b) {
	polynomial ans(max(a.degree(), b.degree()));

	for (int i = 0; i <= max(a.degree(), b.degree()); i++) {
		if (i > a.degree()) {
			ans.p[i] = b.p[i];
		} else if (i > b.degree()) {
			ans.p[i] = a.p[i];
		} else {
			ans.p[i] = a.p[i] + b.p[i];
		}
	}

	return ans;
}

polynomial operator *(polynomial a, long long c) {
	for (fraction &k: a.p) {
		k = k * c;
	}
	return a;
}

polynomial operator *(polynomial a, fraction b) {
	for (fraction &k: a.p) {
		k = k * b;
	}
	return a;
}

polynomial operator -(polynomial a, polynomial b) {
	return a + (b * -1);
}

void init() {
	nCr[0][0] = 1;
	for (int i = 1; i <= 28; i++) {
		nCr[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
		}
	}
}

vector<polynomial> pol;

void solve() {
	for (int p = 0; p <= 26; p++) {
		polynomial lhs(p+1);
		for (int i = 0; i < p; i++) {
			lhs = lhs - (pol[i] * nCr[p+1][i]);
		}
		lhs = lhs * fraction(1, nCr[p+1][p]);
		pol.push_back(lhs);
	}
}

void answer() {
	int t; cin >> t;
	polynomial ans(-1);

	for (int i = 0; i <= t; i++) {
		long long c; cin >> c;
		ans = ans + (pol[i] * c);
	}

	long long res = 0;
	for (fraction k: ans.p) {
		res += abs(k.x);
	}
	cout << res << '\n';
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();

	int t; cin >> t;
	while (t--) {
		answer();
	}

	return 0;
}

