/*
	https://codeforces.com/contest/1142/problem/B

	- Problem summary: we are given a permutation P, and an array A.
	For each query (L, R), determine if the subarray of A from L to R contains a subsequence of a cyclic shift of P.

	------------------------------------------------------------------------------------------------

	- Without loss of generality, we consider P[i] = i for all 1 <= i <= N. 
	We will have to map elements of A to their positions in P first. Let's work on this array instead.
	Let's call a subarray [L, R] "good", if they contain a cyclic shift of P as a subsequence.
	
	- For the purpose of the task, we will consider numbers from 1 to N cyclic. That is, N+1 = 1, and 0 = N.

	- Here are some important observations:
		+ Suppose [L, R] is "good", then any subarray containing [L, R] as another subarray is also good.
		+ For each i, let's define an index j, such that j < i, and a[j] + 1 = a[i]. Let's j be i's "successor".
		  For every index R, we can find the smallest L such that [L, R] is good, by moving along it's successor N times.
		+ If we can find the index L or every R, then for a query [left, right] we can simply do range max query over this range, 
		  and check if max(L) in range [left, right] is not smaller than [left] or not.

	- If we can preprocess and find each L for each index in O(N), we obtain an O(MN + QlogM) solution.

	- The next optimization will improve the preprocessing to O(MlogN).

	------------------------------------------------------------------------------------------------

	- Notice that, for every index i, there can only be one succesor(i). We can find every successors in O(M).

	- Let's introduce the concept of "successor graph", or "functional graph".
	A successor graph is a directed graph, where for each node, there is at most one outcoming edge.

	- Let's build a successor graph with M nodes corresponding to the array A
	There is a node from i to j if j is a succesor of i.

	- Denote a k-successor of i as the node we end up at, suppose we start at i, and walk k times.
	Let's preprocess this graph, and find all succ(i, k) for all i, and k being a power of two from 1 to M.
	We end up with an algorithm that's exactly like binary lifting to find LCA.

	- With this preprocessing, to find a k-successor for arbitrary k, we can use k's binary representation.
	This is again, much like finding LCA with binary lifting.

	- We have made the final optimization, and our preprocessing is now O(MlogN). 
	We obtain a solution with time complexity O(MlogN + QlogM).
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct stmax{
	int n;
	vector<int> a;
	vector<int> tree;

	stmax(vector<int> a, int n) {
		this->a = a;
		this->n = n;
		tree.resize(4*n + 9);
	}

	void build(int node, int start, int end) {
		if(start == end) {
			tree[node] = a[start];
		} else {
			int mid = (start + end)/2;
			
			build(2*node, start, mid);
			build(2*node+1, mid+1, end);
			  
			tree[node] = max(tree[2*node], tree[2*node+1]);
		}
	}

	void update(int node, int start, int end, int index, int val) {
		if (start == end) {
			a[index] = val;
			tree[node] = val;
		} else {
			int mid = (start + end)/2;
			
			if (start <= index && index <= mid) {update(2*node, start, mid, index, val);}
			else {update(2*node+1, mid+1, end, index, val);}
			
			tree[node] = max(tree[2*node], tree[2*node+1]);
		}
	}

	int query(int node, int start, int end, int l, int r) {
		if (r < start || end < l) {
			return 0;
		}
		if (l <= start && end <= r) {
			return tree[node];
		}
		int mid = (start+end)/2;
		return max(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
	}

	int query(int l, int r) {
		return query(1, 1, n, l, r);
	}
};

int clz(int N) {
	return N ? 32 - __builtin_clz(N) - 1 : -100000;
}

int n, m, q;
int p[200001];
int a[200001];
vector<int> lft(200001);

void input() {
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		p[x] = i;
	}
	for (int i = 1; i <= m; i++) {
		int x; cin >> x;
		a[i] = p[x];
	}
}

int succ(int i, int k, int f[][22]) {
	if (k == 0) return i;

	int b = clz(k);
	int x = f[i][b];

	return succ(x, k - (1 << b), f);
}

void solve() {
	int f[200001][22];
	int last[200001];
	memset(f, 0, sizeof(f));
	memset(last, 0, sizeof(last));

	for (int i = 1; i <= m; i++) {
		int k = a[i] - 1;
		if (k == 0) k = n;

		last[a[i]] = i;
		f[i][0] = last[k];
	}

	for (int j = 1; (1 << j) < m; j++) {
		for (int i = 1; i <= m; i++) {
			if(f[i][j-1] != 0){
				f[i][j] = f[f[i][j-1]][j-1] ;
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		lft[i] = succ(i, n-1, f);
	}
}

void output() {
	stmax st(lft, m);
	st.build(1, 1, m);

	while (q--) {
		int l, r; cin >> l >> r;
		cout << (st.query(l, r) >= l);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	input();
	solve();
	output();
	
	return 0;
}