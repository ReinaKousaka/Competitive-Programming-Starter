#include <bits/stdc++.h>
using namespace std;


void solve() {
	int n;
	cin >> n;
	vector<vector<int>> a(n);
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		while (k--) {
			int x;
			cin >> x;
			if (a[i].empty() || x > a[i].back()) {
				a[i].push_back(x);
			}
		}
	}

	std::sort(a.begin(), a.end(),
		[](auto& x, auto& y) {
			return x.back() < y.back();
		});

	// dp[i] := max impression we can get from albums 0..i-1
	vector<int> dp(n), back_vals;
	dp[0] = a[0].size();
	back_vals.push_back(a[0].back());

	for (int i = 1; i < n; i++) {
		// initial: assume we skip this album or only take this album
		dp[i] = std::max(dp[i - 1], (int) a[i].size());
		for (int j = 0; j < a[i].size(); j++) {
			int idx = std::distance(
				back_vals.begin(),
				std::lower_bound(back_vals.begin(), back_vals.end(), a[i][j])
			) - 1;
			if (idx >= 0) {
				dp[i] = std::max(dp[i], dp[idx] + (int)a[i].size() - j);
			}
		}
		back_vals.push_back(a[i].back());
	}

	cout << dp.back() << "\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}