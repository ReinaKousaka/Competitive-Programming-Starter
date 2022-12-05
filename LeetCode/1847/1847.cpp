#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        // mark down original index
        for (int i = 0; i < queries.size(); i++) {
            queries[i].push_back(i);
        }
        // sort based on room size
        sort(rooms.begin(), rooms.end(),
            [](auto& a, auto& b)->bool { return a[1] > b[1]; }
        );
        sort(queries.begin(), queries.end(),
            [](auto& a, auto& b)->bool { return a[1] > b[1]; }
        );
        // for each query, add rooms with size greater or equal to it
        set<int> s;     // storing indices
        vector<int> res(queries.size());
        int i = 0;
        for (auto& query: queries) {
            while (i < rooms.size() && rooms[i][1] >= query[1]) {
                s.emplace(rooms[i][0]);
                i++;
            }
            auto it = s.lower_bound(query[0]);
            if (!s.size()) {
                res[query[2]] = -1;
            } else if (it == s.end()) {
                res[query[2]] = *(next(it, -1));
            } else if (it == s.begin()) {
                res[query[2]] = *it;
            } else {
                res[query[2]] = (abs(*it - query[0]) < abs(*(next(it, -1)) - query[0])) 
                    ? *it : *(next(it, -1));
            }
        }
        return res;
    }
};