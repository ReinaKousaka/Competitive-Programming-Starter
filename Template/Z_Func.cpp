#include <string>
#include <vector>
#include <algorithm>


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
