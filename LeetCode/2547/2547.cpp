#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        // dp[i] := the min cost to split nums[0..i - 1]
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // dummy 0
        for (int i = 0; i < n; i++) {
            // calculate trimmed(nums[j..i])
            unordered_map<int, int> counter;
            int importance = k;
            for (int j = i; j >= 0; j--) {
                counter[nums[j]]++;
                if (counter[nums[j]] == 2) {
                    importance += 2;
                } else if (counter[nums[j]] > 2) {
                    importance++;
                }

                dp[i + 1] = min(dp[j] + importance, dp[i + 1]);
            }
        }
        return dp[n];
    }
};
