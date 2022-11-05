#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct TrieNode {
    vector<TrieNode*> children = vector<TrieNode*>(26, nullptr);
    string word = "";
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // construct Trie
        TrieNode* root = new TrieNode();
        for (auto& word: words) {
            TrieNode* curr = root;
            for (auto& ch: word) {
                if (!curr->children[ch - 'a']) {
                    curr->children[ch - 'a'] = new TrieNode();
                }
                curr = curr->children[ch - 'a'];
            }
            curr->word = word;
        }

        unordered_set<string> set;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, root, i, j, set);
            }
        }
        vector<string> res;
        for (auto& word: set) {
            res.push_back(word);
        }
        return res;
    }

    void dfs(vector<vector<char>>& board, TrieNode* curr,
        int i, int j, unordered_set<string>& set
    ) {
        auto ch = board[i][j];
        // return if visited the cell before or not a word 
        if (board[i][j] == '!' || !curr->children[ch - 'a']) {
            return;
        }
        // moves ptr and check word
        curr = curr->children[ch - 'a'];
        if (curr->word != "") {
            set.insert(curr->word);
        }
        // backtrack
        board[i][j] = '!';      // mark as visited
        if (i > 0) dfs(board, curr, i - 1, j, set);
        if (j > 0) dfs(board, curr, i, j - 1, set);
        if (i < board.size() - 1) dfs(board, curr, i + 1, j, set);
        if (j < board[0].size() - 1) dfs(board, curr, i, j + 1, set);
        board[i][j] = ch;       // reset
    }
};