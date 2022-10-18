#include <vector>
using namespace std;

class Solution {
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int sum = 0, n = nums.size();
        for (auto num: nums) { sum += num; }
        vector<vector<int>> neighbors(n, vector<int>());
        for (auto& edge: edges) {
            neighbors[edge[0]].push_back(edge[1]);
            neighbors[edge[1]].push_back(edge[0]);
        }
        for (int i = 1; i <= sum / 2; i++) {
            if (sum % i) { continue; }
            // go through all factors from smallest
            if (!dfs(0, -1, i, nums, neighbors)) {
                return sum / i - 1;
            }
        }
        return 0;
    }

    // the cut is always a complete subtree
    int dfs(int curr, int parent, int target, vector<int>& nums, vector<vector<int>>& neighbors) {
        int sum = nums[curr];
        for (auto child: neighbors[curr]) {
            if (child == parent) { continue; }
            int res = dfs(child, curr, target, nums, neighbors);
            if (res == -1) {
                // invalid
                return -1;
            }
            sum += res;
            if (sum > target) {
                return -1;
            }
        }
        if (sum == target) {
            // find a valid component, delete it by setting sum to 0
            return 0;
        } else {
            return sum;
        }
    }
};