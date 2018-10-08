/*
      http://community.topcoder.com/stat?c=problem_statement&pm=12527

      - First, we will rotate the board by 45 degrees. This means a point (x, y) becomes (X-Y, X+Y) after the rotation.
      After the rotation, the original manhattan distance is now equal to the new chebyshev distance.
      That is, the maximum difference of the X and Y coordinate (instead of the sum).

      - Let's see what happens when we add a point to an already-added set of points:
      The added set of points will form a rectangular region. The "cost" of this addition is the maximum distance from the new point to each of the sides.

      - We will do dynamic programming on this rectangle. We will try to expand this rectangle, each time by one unit on a single side.
      The state of this rectangle will be the coordinate of the 4 sides of this rectangle.
      This gives us 16^4 states in total, as our rotated chessboard is of size 16*16.

      - Each time we expand this rectangle, we will have to add the costs of all the points that lie in the newly-expanded side.

      - We can have a maximum of 64 points on the chessboard. Therefore our total complexity will be O(N^6), with N being the dimension of the rotated board.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class EllysChessboard{
public:
	int b[20][20];
	int dp[20][20][20][20];
	vector<int> x, y;

	int solve(int up, int left, int down, int right) {
		if (dp[up][left][down][right] == -1) {
			long long mask = 0;

			for (int i = 0; i < x.size(); i++) {
				if (x[i] < up || x[i] > down || y[i] < left || y[i] > right) mask |= 1LL << i;
			}

			if (mask == 0) {dp[up][left][down][right] = 0;}
			else {
				dp[up][left][down][right] = 100000000;

				for (int dir = 0; dir < 4; dir++) {
					int u = up - (dir == 0);
					int d = down + (dir == 1);
					int l = left - (dir == 2);
					int r = right + (dir == 3);

					if (u < 0 || d >= 16 || l < 0 || r >= 16) continue;

					int cost = 0;
					for (int i = 0; i < x.size(); i++) {
						if (mask & (1LL << i)) {
							if (x[i] >= u && x[i] <= d && y[i] <= r && y[i] >= l) {
								cost += max(max(abs(x[i] - u), abs(d - x[i])), max(abs(l - y[i]), abs(y[i] - r)));
							}
						}
					}

					dp[up][left][down][right] = min(dp[up][left][down][right], cost + solve(u, l, d, r));
				}
			}
		}

		return dp[up][left][down][right];
	}

	int minCost(vector<string> s) {
		memset(b, 0, sizeof(b));
		memset(dp, -1, sizeof(dp));

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (s[i][j] == '#') {
					x.push_back(i+j+1);
					y.push_back(i-j+8);

					b[i-j+8][i+j+1] = 1;
				}
			}
		}

		if (x.size() <= 1) return 0;

		int ans = 100000000;
		for (int i = 0; i < x.size(); i++) {
			ans = min(ans, solve(x[i], y[i], x[i], y[i]));
		}
		return ans;
	}
};
