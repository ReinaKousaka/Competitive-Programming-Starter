#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        vector<pair<int, int>> time;    // {grow, plant}
        int n = plantTime.size();
        for (int i = 0; i < n; i++) {
            time.push_back({growTime[i], plantTime[i]});
        }
        // greedily plant flowers with larger growTime first
        sort(time.begin(), time.end(), greater<pair<int, int>>());
        int day = 0, res = 0;
        for (auto& [gt, pt]: time) {
            res = max(res, day + pt + gt);
            day += pt;
        }
        return res;
    }
};