#include <bits/stdc++.h>
using namespace std;


std::vector<int> KMP(const std::string& s, const std::string& t) {
    // find all occurences of s in t
    auto prefix_function = [](const std::string& s) {
        /** https://cp-algorithms.com/string/prefix-function.html
         * pi[i] := the length of the longest proper prefix of the substring s[0..i]
         * which is also the suffix of the substring. pi[0] := 0
         * */
        int n = s.size();
        std::vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = pi[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            pi[i] = j;
        }
        return pi;
    };

    // assume '#' does not appear in s or t
    auto pref = prefix_function(s + "#" + t);
    std::vector<int> occurences;
    int n = s.size(), m = t.size();
    for (int i = n + 1; i < n + m + 1; i++) {
        if (pref[i] == n) {
            occurences.push_back(i - 2 * n);
        }
    }
    return occurences;
}


class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        auto occur_a = KMP(a, s), occur_b = KMP(b, s);
        set<int> sb(occur_b.begin(), occur_b.end());
        vector<int> res;
        for (auto x: occur_a) {
            auto it = sb.lower_bound(x);
            int min_diff = k + 1;
            if (it != sb.end()) {
                min_diff = std::min(min_diff, *it - x);
            }
            if (it != sb.begin()) {
                it--;
                min_diff = std::min(min_diff, x - *it);
            }
            if (min_diff <= k) {
                res.push_back(x);
            } 
        }
        return res;
    }
};
