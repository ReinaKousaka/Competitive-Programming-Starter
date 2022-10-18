#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        // true if s[i..j] is palindrome
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, true));
        // DP
        for (int l = 1; l < n; l++) {
            for (int i = 0, j = i + l; j < n; i++, j++) {
                isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i + 1][j - 1]); 
            }
        }

        // dp[i] := min # cuts to cut s[1..i]
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (isPalindrome[j][i]) {
                    if (!j) {
                        // special case, s[0..i] is panlindrome
                        dp[i] = 0;
                    } else {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                }
            }
        }
        return dp[n - 1];
    }
};