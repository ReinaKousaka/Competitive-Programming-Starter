#include <bits/stdc++.h>
using namespace std;


void solve() {
	int n, k, d, w;
	cin >> n >> k >> d >> w;
	vector<int> t(n);
	for (int i = 0; i < n; i++) {
		cin >> t[i];
	}
	int res = 0;
	int i = 0;
	while (i < n) {
		res++;
		int j = i;
		while (j < n && t[j] - t[i] <= d + w && j - i < k) {
			j++;
		}
		i = j;
	}
	cout << res << "\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
