#include <bits/stdc++.h>
using namespace std;


// Digit DP template
long long dfs(const string& bound, int pos, int non_zero, bool tight,
	vector<vector<long long>>& dp)
{
	if (pos >= bound.size()) return 1;
	if (!tight && dp[pos][non_zero] != -1) return dp[pos][non_zero];
	
	long long res = 0;
	for (int i = 0; i <= (tight ? bound[pos] - '0' : 9); i++) {
		if (i && non_zero == 3) continue;
		res += dfs(bound, pos + 1, non_zero + (i > 0), tight && (i == bound[pos] - '0'), dp);
	}
	if (!tight) {
		dp[pos][non_zero] = res;
	}
	return res;
}

void solve() {
	long long l, r;
	cin >> l >> r;

	auto run_dfs = [](long long x) {
		string s = std::to_string(x);
		vector<vector<long long>> dp(s.size(), vector<long long>(4, -1));
		return dfs(s, 0, 0, true, dp);
	};

	cout << run_dfs(r) - run_dfs(l - 1) << "\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
