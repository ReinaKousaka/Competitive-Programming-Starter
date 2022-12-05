#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int l = 0, r = 0;
        int flip = 0, res = 0;
        while (r < nums.size()) {
            // add nums[r]
            if (!nums[r]) {
                flip++;
            }
            // shrink
            while (flip > 1) {
                if (!nums[l]) {
                    flip--;
                }
                l++;
            }
            r++;
            res = max(res, r - l);   
        }
        return res;
    }
};