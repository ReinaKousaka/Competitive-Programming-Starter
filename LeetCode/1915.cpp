#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
	long long wonderfulSubstrings(string word) {
		// dp[i] := # string prefixs XOR sum of value mask i
		vector<int> dp(1024, 0);
		dp[0] = 1;
		int mask = 0;
		long long res = 0;
		for (auto ch: word) {
			mask ^= 1 << (ch - 'a');
			res += dp[mask];
			for (int i = 0; i < 10; i++) {
				int temp = mask ^ (1 << i);
				res += dp[temp];
			}
			dp[mask]++;
		}
	return res;
	}
};
