#include <bits/stdc++.h>
using namespace std;


// Digit DP template
void dfs(const string& lower, const string& upper, 
	int pos, int min, int max, bool tight_lower, bool tight_upper,
	vector<vector<vector<vector<vector<bool>>>>>& dp,
	string& curr, int& min_lucky, string& res)
{
	if (pos >= lower.size()) {
		// get a valid number
		if (max - min < min_lucky) {
			min_lucky = max - min;
			res = curr;
		}
		return;
	}

	if (dp[pos][min][max][tight_lower][tight_upper]) return;
	if (max - min >= min_lucky) return;
	// mark current state as visited
	dp[pos][min][max][tight_lower][tight_upper] = 1;	

	for (int i = (tight_lower ? lower[pos] - '0' : 0);
		i <= (tight_upper ? upper[pos] - '0' : 9); i++)
	{
		curr[pos] = i + '0';
		dfs(lower, upper, pos + 1, std::min(min, i), std::max(max, i),
			tight_lower && i == lower[pos] - '0', tight_upper && i == upper[pos] - '0',
			dp, curr, min_lucky, res);
	}
}


void solve() {
	long long l, r;
	cin >> l >> r;

	string sl = to_string(l), sr = to_string(r);
	if (sl.size() < sr.size()) {
		cout << string(sr.size() - 1, '9') << "\n";
		return;
	}
	
	int n = sl.size();
	// dp[pos][min_digit][max_digit][tight_lower][tight_upper], true if the state is visited
	// min, max: current min/max digit
	// tight = 0 --> can pick digits arbitrarily

	// bool dp[n][10][10][2][2];
	// std::fill_n(&dp[0][0][0][0][0], n * 10 * 10 * 2 * 2, 0);
	vector<vector<vector<vector<vector<bool>>>>> dp(n,
		vector<vector<vector<vector<bool>>>>(10,
			vector<vector<vector<bool>>>(10,
				vector<vector<bool>>(2,
					vector<bool>(2, false)))));

	string curr = string(n, '0'), res;
	int min_lucky = 10;
	dfs(sl, sr, 0, 9, 0, 1, 1, dp, curr, min_lucky, res);

	cout << res << "\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
