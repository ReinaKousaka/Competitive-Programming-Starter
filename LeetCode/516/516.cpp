#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        // dp[i][j]:= the longest palindromic subsequence of s[i..j]
        vector<vector<int>> dp(n, vector<int>(n, 1));
        // bellman equation:
        for (int l = 1; l < n; l++) {
            for (int i = 0, j = i + l; j < n; i++, j++) {
                // 1. take the longer length of subsequence s[(i+1)..j] and s[i..(j-1)]
                // i.e. when head/tail is not used in the palindromic subsequence
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);

                // 2. when head = tail, they can be one pair of palindromic chars
                // add it to the optimal length inner
                if (s[i] == s[j]) {
                    if (l == 1) {
                        // handle special case of i + 1 == j
                        dp[i][j] = max(dp[i][j], 2);
                    } else {
                        dp[i][j] = max(dp[i][j], 2 + dp[i + 1][j - 1]);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};