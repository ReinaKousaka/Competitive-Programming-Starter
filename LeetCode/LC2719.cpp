#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Digit DP template
int dfs(const string& bound, int pos, int dsum, bool tight,
	vector<vector<int>>& dp, int min_sum, int max_sum)
{
	if (dsum > max_sum) return 0;
	if (pos >= bound.size()) return dsum >= min_sum;
	if (!tight && dp[pos][dsum] != -1) return dp[pos][dsum];
	
	int res = 0;
	for (int i = 0; i <= (tight ? bound[pos] - '0' : 9); i++) {
		res = (res + dfs(bound, pos + 1, dsum + i, tight && (i == bound[pos] - '0'), dp, min_sum, max_sum)) % MOD;
	}
	if (!tight) {
		dp[pos][dsum] = res;
	}
	return res;
}


class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        vector<vector<int>> dp(num1.size(), vector<int>(max_sum + 1, -1));
       	auto res1 = dfs(num1, 0, 0, true, dp, min_sum, max_sum);
       	cout << res1 << " ";


		dp.resize(num2.size(), vector<int>(max_sum + 1, -1));
       	auto res2 = dfs(num2, 0, 0, true, dp, min_sum, max_sum);
       	cout << res2 << " ";

		int cnt = 0;
		for (auto ch: num1) {
			cnt += ch - '0';
		}
		int extra = 0;
		if (cnt >= min_sum && cnt <= max_sum)
			extra = 1;
       	int res = (res2 - res1 + extra) % MOD;
       	return res < 0 ? res + MOD : res; 
    }
};
