#include <string>
#include <vector>
using namespace std;

// calculate the "next" array of KMP algorithm
vector<int> KMP_next_array(const string& p) {
    // next[i] := the max length of suffix starting at i backwards in p which matches some prefix of p
    vector<int> next = {0};
    int i = 1, now = 0;
    while (i < p.size()) {
        if (p[now] == p[i]) { // expands right
            now++;
            i++;
            next.push_back(now);
        } else if (now) {       // shrink
            now = next[now - 1];
        } else {
            next.push_back(0);
            i++;
        }
    }
    return next;
}

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        s += '!';
        for (int i = n - 1; i >= 0; i--) {
            s += s[i];
        }
        auto next = KMP_next_array(s);
        int len = next.back();
        string res;
        for (int i = n - 1; i > n - 1 - (n - len); i--) {
            res += s[i];
        }
        for (int i = 0; i < n; i++) {
            res += s[i];
        }
        return res;
    }
};
