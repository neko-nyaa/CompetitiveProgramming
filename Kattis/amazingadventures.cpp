/*
	https://open.kattis.com/problems/amazingadventures

	- Just do two standard BFS. Try to find path from B->C, then C->G. 
	If that doesn't work, try G->C then B->C. If either one works then it's "YES", otherwise "NO".
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 10000000;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char dir[] = {'L', 'R', 'D', 'U'};
char dinv[] = {'R', 'L', 'U', 'D'};

vector<char> invert(vector<char> c) {
	vector<char> ans;
	while (c.size()) {
		char k = c.back(); c.pop_back();

		for (int i = 0; i < 4; i++) {
			if (k == dir[i]) ans.push_back(dinv[i]);
		}
	}
	return ans;
}

vector<char> find_path(int n, int m, vector<vector<char>> &c, int bx, int by, int cx, int cy) {
	// b to c

	vector<vector<int>> dist(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = INF;
		}
	}

	queue<pair<int, int>> q;
	q.push({bx, by}); dist[bx][by] = 0;
	while (q.size() && dist[cx][cy] == INF) {
		auto kkk = q.front(); q.pop();
		int x, y; tie(x, y) = kkk;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < n && nx >= 0 && ny < m && ny >= 0 && c[nx][ny] == '.' && dist[x][y] + 1 < dist[nx][ny]) {
				dist[nx][ny] = dist[x][y] + 1;
				q.push({nx, ny});
			}
		}
	}
	if (dist[cx][cy] == INF) return vector<char>(0);

	vector<char> ans;
	int x = cx, y = cy;
	while (x != bx || y != by) {

		int mn = INF;
		char move;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < n && nx >= 0 && ny < m && ny >= 0) {
				mn = min(mn, dist[nx][ny]);
			}
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < n && nx >= 0 && ny < m && ny >= 0) {
				if (dist[nx][ny] == mn) {
					c[nx][ny] = '*'; x = nx; y = ny; move = dir[i]; 
					break;
				}
			}
		}
		ans.push_back(move);
	}

	return invert(ans);
}

vector<char> solve(int n, int m, vector<vector<char>> c, int bx, int by, int cx, int cy, int gx, int gy, int inverse) {
	// b to c, then c to g

	c[gx][gy] = '*'; vector<char> bc = find_path(n, m, c, bx, by, cx, cy);
	c[gx][gy] = '.'; vector<char> cg = find_path(n, m, c, cx, cy, gx, gy);

	if (bc.empty() || cg.empty()) {
		return vector<char>(0); 
	} else {
		vector<char> ans;
		for (char cc: bc) ans.push_back(cc);
		for (char cc: cg) ans.push_back(cc);

		if (inverse) {
			ans = invert(ans);
		}
		return ans;
	}
}


void solve(int n, int m) {
	vector<vector<char>> c(n, vector<char>(m, '.'));

	int bx, by; cin >> bx >> by; bx--; by--;
	int cx, cy; cin >> cx >> cy; cx--; cy--;
	int gx, gy; cin >> gx >> gy; gx--; gy--;
	int ux, uy; cin >> ux >> uy; ux--; uy--;
	c[ux][uy] = '*';

	vector<char> ans;
	int dist = INF;

	vector<char> tmp = solve(n, m, c, bx, by, cx, cy, gx, gy, 0);
	if (tmp.size() > 0 && tmp.size() < dist) {
		ans = tmp;
		dist = tmp.size();
	}

	tmp = solve(n, m, c, gx, gy, cx, cy, bx, by, 1);
	if (tmp.size() > 0 && tmp.size() < dist) {
		ans = tmp;
		dist = tmp.size();
	}

	if (ans.size() > 0) {
		cout << "YES\n";
		for (char c: ans) cout << c;
		cout << '\n';
	} else {
		cout << "NO\n";
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	while (cin >> n >> m, n, m) {
		solve(n, m);
	}

	return 0;
}
