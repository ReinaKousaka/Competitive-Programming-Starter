#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        // true if s[i..j] is palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, true));
        for (int l = 1; l < n; l++) {
            for (int i = 0, j = i + l; j < n; i++, j++) {
                dp[i][j] = (dp[i + 1][j - 1] && s[i] == s[j]); 
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = n - 2; j >= i; j--) {
                if (dp[0][i - 1] && dp[i][j] && dp[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};