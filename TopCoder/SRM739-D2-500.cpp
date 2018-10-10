/*
      https://community.topcoder.com/stat?c=problem_statement&pm=15095&rd=17298&rm=331762&cr=40629265

      - Given current time, and time of event, find out if event is "few seconds ago", "X minutes ago", or "X hours ago".

      - We will convert the time from HH:MM:SS to seconds. This is much easier to work with.
      Be careful, as time of event might be from the day before current time.

      - Editorial uses stringstream, very elegant in my opinion. The solution is in the link below:
      https://www.topcoder.com/blog/single-round-matches-739-editorials/
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class ForumPostMedium{
public:
	int tonum(string k) {
		return (k[0] - '0')*10 + (k[1] - '0');
	}

	int getsec(string t) {
		string h, m, s;
		h += t[0]; h += t[1];
		m += t[3]; m += t[4];
		s += t[6]; s += t[7];

		int ans = tonum(s);
		ans += tonum(m)*60;
		ans += tonum(h)*3600;

		return ans;
	}

	string getShownPostTime(string currentTime, string exactPostTime) {
		int cur = getsec(currentTime);
		int exa = getsec(exactPostTime);

		if (exa > cur) {
			cur += 86400;
		}

		if (cur - exa <= 59) {
			return "few seconds ago";
		} else if (cur - exa < 3600) {
			string ans;
			ans += to_string((cur - exa)/60);
			ans += " minutes ago";
			return ans;
		} else {
			string ans;
			ans += to_string((cur - exa)/3600);
			ans += " hours ago";
			return ans;
		}

		string s; return s;
	}
};
