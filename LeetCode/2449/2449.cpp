#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> odd, even, odd_target, even_target;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2) {
                odd.push_back(nums[i]);
            } else {
                even.push_back(nums[i]);
            }
            if (target[i] % 2) {
                odd_target.push_back(target[i]);
            } else {
                even_target.push_back(target[i]);
            }
        }
        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());
        sort(odd_target.begin(), odd_target.end());
        sort(even_target.begin(), even_target.end());
        long long res = 0;
        for (int i = 0; i < odd.size(); i++) {
            if (odd[i] < odd_target[i]) {
                res += (odd_target[i] - odd[i]) / 2;
            }
        }
        for (int i = 0; i < even.size(); i++) {
            if (even[i] < even_target[i]) {
                res += (even_target[i] - even[i]) / 2;
            }
        }
        return res;
    }
};