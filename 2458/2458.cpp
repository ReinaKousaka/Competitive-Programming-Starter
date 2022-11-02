#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    const int MAX = 1e5 + 1;
    vector<int> heights = vector<int>(MAX, -1);
    vector<int> depths = vector<int>(MAX, -1);

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        // DFS calculate height, depth for each node
        dfs(root);
        // BFS calculate values of top 2 heights for each layer
        vector<vector<int>> top_two_heights(
            heights[root->val] + 1, vector<int>(2, 0)
        );   // i-th index means i-th layer from root down to leaves
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0; 
        heights[0] = -1;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode* curr = q.front();
                q.pop();
                if (curr->left) { q.push(curr->left); } 
                if (curr->right) { q.push(curr->right); } 
                // compare values, get top 2
                if (heights[curr->val] >= heights[top_two_heights[depth][0]]) {
                    top_two_heights[depth][1] = top_two_heights[depth][0];
                    top_two_heights[depth][0] = curr->val;
                } else if (heights[curr->val] > heights[top_two_heights[depth][1]]) {
                    top_two_heights[depth][1] = curr->val;
                }
            }
            depth++;
        }

        // delete a subtree rooted at layer of depth i
        // if i is the top 1 heights, return top 2 heights + i
        // otherwise, return top 1 heights + i
        vector<int> res;
        for (auto& query: queries) {
            int depth = depths[query];
            if (top_two_heights[depth][0] == query) {
                res.push_back(heights[top_two_heights[depth][1]] + depth);
            } else {
                res.push_back(heights[top_two_heights[depth][0]] + depth);
            }
        }
        return res;
    }

    void dfs(TreeNode* root, int depth=-1) {
        depth++;
        depths[root->val] = depth;
        // base case for leaves
        if (!root->left && !root->right) {
            heights[root->val] = 0;
            return;
        }
        
        int l = 0, r = 0;
        if (root->left) { 
            dfs(root->left, depth);
            l = heights[root->left->val];
        }
        if (root->right) { 
            dfs(root->right, depth); 
            r = heights[root->right->val];
        }
        heights[root->val] = max(l, r) + 1;
    }
};