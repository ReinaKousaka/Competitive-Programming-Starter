#include <vector>
#include <deque>
#include <utility>
using namespace std;

// decreasing monotonic deque (max) template
// push to back(right)
template <typename T>
class Monoqueue {
 public:
    std::deque<pair<T, int>> dq;   // (val, index)
    int index = 0;
    Monoqueue() {}

    // delete all elements in deque with index < index_lower_bound
    void push_back(T val, int index_lower_bound=0) {
        pop_front_with_index_lower_bound(index_lower_bound);
        while (dq.size() && dq.back().first < val) {
            dq.pop_back();
        }
        dq.push_back({val, index++});
    }

    void pop_front_with_index_lower_bound(int index_lower_bound) {
        while (dq.size() && dq.front().second < index_lower_bound) {
            dq.pop_front();        
        }
    }

    void pop_front() {
        dq.pop_front();
    }

    T get_max() {
        return dq.front().first;
    }
};

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        Monoqueue<int> dp;
        dp.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            dp.pop_front_with_index_lower_bound(i - k);     // remove all values out of range
            if (i == nums.size() - 1) {
                return dp.get_max() + nums.back();
            }
            dp.push_back(nums[i] + dp.get_max());       // the max score ending at i is max(i - k, .. , i - 1) + nums[i]
        }
        return dp.get_max();        // only executes when nums.size() == 1
    }
};
