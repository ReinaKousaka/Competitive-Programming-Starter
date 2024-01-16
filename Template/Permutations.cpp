#include <vector>
#include <unordered_set>


void _addPermute(std::vector<int>& nums, int start, std::vector<std::vector<int>>& res) {
    int n = nums.size();
    if (start == n) {
        res.push_back(nums);
        return;
    }
    std::unordered_set<int> s;
    for (int i = start; i < n; i++) {
        if (s.find(nums[i]) == s.end()) {
            s.emplace(nums[i]);
            std::swap(nums[i], nums[start]);
            _addPermute(nums, start + 1, res);
            // reset
            std::swap(nums[i], nums[start]);
        }
    }
}

std::vector<std::vector<int>> get_unique_permutation(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    _addPermute(nums, 0, res);
    return res;
}