#include <bits/stdc++.h>
using namespace std;


/**
 * Z function template
 * z[i] := the longest common prefix of s and s[i .. n - 1], given string s
 **/
std::vector<int> z_func(const std::string& s) {
	int l = 0, r = 0;
	int n = s.size();
	std::vector<int> z(n);
	for (int i = 1; i < n; i++) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			z[i] = std::max(r - i + 1, 0);
			while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
				z[i]++;
			}
		}
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;
}

// ceil(a / b), where a, b > 0
inline int ceil_div(int a, int b) {
    return (a + b - 1) / b;
}

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        auto z = z_func(word);
        int n = word.size();
        int res = ceil_div(n, k);
        for (int i = k; i < n; i += k) {
        	if (z[i] + i >= n)
        		res = std::min(res, ceil_div(n - z[i], k));
        }
        return res;
    }
};
