#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

class Solution {
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        // the end points of the path must be a leaf node or the root
        vector<vector<int>> neighbors(n, vector<int>());
        for (auto& edge: edges) {
            int a = edge[0], b = edge[1];
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
        ll res = 0;
        dfs(0, -1, res, neighbors, price);
        return res;
    }

    // calculate the max price of paths which make a turn at root
    // return (max sum from root to a leaf, max sum from root to a leaf without leaf value)
    pair<ll, ll> dfs(int root, int parent, ll& res, 
        vector<vector<int>>& neighbors, vector<int>& price
    ) {
        ll max_with_leaf = price[root];
        ll max_no_leaf = 0;
        for (int child: neighbors[root]) {
            if (child == parent) continue;
            auto [sum1, sum2] = dfs(child, root, res, neighbors, price);
            // update res, two cases: the child path is with/without the leaf
            res = max<ll>({res, 
                sum1 + max_no_leaf, 
                sum2 + max_with_leaf
            });

            max_with_leaf = max(max_with_leaf, sum1 + price[root]);
            max_no_leaf = max(max_no_leaf, sum2 + price[root]);
        }
        return {max_with_leaf, max_no_leaf};
    }
};
