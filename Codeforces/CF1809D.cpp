#include <bits/stdc++.h>
using namespace std;


void solve() {
	string s;
	cin >> s;
	int n = s.size();
	vector<vector<long long>> dp(n, vector<long long>(3));
	/** 
	 * dp[i][0]: min cost to make s[0..i] valid and ends with 0
	 * dp[i][1]: min cost to make s[0..i] valid and ends with 01
	 * dp[i][2]: min cost to make s[0..i] valid and ends with 11
	 * Note we can add a dummy 0 at the beginning
	 * */
	const long long INF = 1LL << 60;
	const long long C = 1e12;
	dp[0][0] = (s[0] == '0') ? 0 : C + 1;
	dp[0][1] = (s[0] == '1') ? 0 : INF;
	dp[0][2] = INF;

	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] + (s[i] == '1' ? C + 1 : 0);
		if (s[i] == '1') {
			dp[i][0] = dp[i - 1][0] + C + 1;
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + C + 1);
			dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
		} else {
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1] + C);
			dp[i][2] = dp[i - 1][2] + C + 1;
		}
	}
	cout << std::min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]}) << "\n";
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
