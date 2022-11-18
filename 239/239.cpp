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
        while (dq.size() && dq.front().second < index_lower_bound) {
            dq.pop_front();        
        }
        while (dq.size() && dq.back().first < val) {
            dq.pop_back();
        }
        dq.push_back({val, index++});
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
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        Monoqueue<int> mq;
        for (int i = 0; i < k - 1; i++) {
            mq.push_back(nums[i]);
        }
        vector<int> res;
        for (int i = k - 1; i < nums.size(); i++) {
            mq.push_back(nums[i], i - k + 1);
            res.push_back(mq.get_max());
        }
        return res;
    }
};
