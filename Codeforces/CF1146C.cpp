#include <bits/stdc++.h>
using namespace std;


// query 1, (r - l + 1), 1, l .. r
int query(int l, int r) {
	cout << 1 << " " << r - l + 1 << " " << 1 << " ";
	for (int i = l; i <= r; i++) {
		cout << i << " \n"[i == r];
	}
	cout.flush();
	int res;
	cin >> res;
	return res;
}


void solve() {
	int n;
	cin >> n;

	int d1 = query(2, n);
	
	// binary search to find node x s.t. dist(1, x) = d1
	int lo = 2, hi = n;
	int x;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (query(lo, mid) < d1) {
			lo = mid + 1;
		} else {
			x = mid;
			hi = mid - 1;
		}
	}

	// find max dist(x, y) for any y
	cout << 1 << " " << n - 1 << " " << x << " ";
	for (int i = 1; i <= n; i++) {
		if (i == x) continue;
		cout << i << " ";
	}
	cout << "\n";
	cout.flush();
	int res;
	cin >> res;
	cout << -1 << " " << res << "\n";
	cout.flush();
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	
	while (t--) solve();
	return 0;
}

