#include <vector>
using namespace std;

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int mod = 7 + 1e9;
        int n = nums.size();
        long long sum = 0;
        int res = 1;      // 2^n initially
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            res = (res * 2) % mod;
        }
        // don't need to worry about both groups sum < k
        if (sum < 2 * k) return 0;

        // total: 2^n groups; both group < k and its compliment are invalid
        // use knapsack-like dp to count those groups whose sum < k
        vector<vector<int>> dp(n + 1, vector<int>(k, 0));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < k; j++) {
            for (int i = 1; i <= n; i++) {
                if (j >= nums[i - 1]) {
                    dp[i][j] = (dp[i - 1][j - nums[i - 1]] + dp[i - 1][j]) % mod;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }   
        }

        for (int j = 0; j < k; j++) {
            res = (res - (2 * dp[n][j]) % mod) % mod;
        }
        return res >= 0 ? res : res + mod;
    }
};
