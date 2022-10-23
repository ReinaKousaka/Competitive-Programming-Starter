#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// both methods are O(nlogn)

// method 1: prefix sum array
/**
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = nums.size();
        vector<pair<int, int>> arr;
        vector<long long> prefix(n, 0);
        vector<long long> suffix(n, 0);
        long long res = 0;
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], cost[i]});
        }
        sort(arr.begin(), arr.end());       // sort based on val
        // create prefix, suffix sum cost array
        for (int i = 0; i < n; i++) {
            prefix[i] = prefix[max(0, i - 1)] + arr[i].second;
            suffix[n - 1 - i] = suffix[min(n - 1, n - i)] + arr[n - 1 - i].second;
            if (i) {
                res += ((long long)arr[i].second) * abs(arr[i].first - arr[0].first);
            }
        }
        // try all possible targets
        long long curr = res;
        for (int i = 1; i < n; i++) {
            int delta = arr[i].first - arr[i - 1].first;
            curr = curr - ((long long)delta * suffix[i]) + ((long long)delta * prefix[i - 1]);
            res = min(res, curr);
        }
        return res;
    }
};
*/

// method 2: Ternary Search
// https://cp-algorithms.com/num_methods/ternary_search.html
// f(x) must be unimodal on the interval
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int l = *min_element(nums.begin(), nums.end());
        int r = *max_element(nums.begin(), nums.end());
        long long res = -1;
        while (l <= r) {
            int mid1 = l + (r - l) / 3;
            int mid2 = r - (r - l) / 3;
            long long c1 = 0, c2 = 0;
            for (int i = 0; i < nums.size(); i++) {
                c1 += ((long long)abs(mid1 - nums[i]) * cost[i]);
                c2 += ((long long)abs(mid2 - nums[i]) * cost[i]);
            }
            if (c1 <= c2) {
                r = mid2 - 1;
            } else {
                l = mid1 + 1;
            }
            res = (res == -1) ? min(c1, c2) : min({res, c1, c2});
        }
        return res;
    }
};