#include <bits/stdc++.h>
using namespace std;


/**
 * SparseTable template (0-indexed, max)
 * query min/max/gcd, idempotent functions: O(1), query sum: O(log {n})
 * f[i, j] := the min/max/gcd among the range [i + 2^j -1, i]
 * for a query on [l, r]: split it into [l, l + 2^s - 1] & [r - 2^s + 1, r],
 * where s = floor(log_2 {r - l + 1})
 */
template<typename T>
struct SparseTable {
	const int n;
	std::vector<std::vector<T>> f;
	std::vector<int> logs;
	
	SparseTable(std::vector<T> data): n(data.size()), logs(n + 1) {
		logs[1] = 0, logs[2] = 1;
		for (int i = 3; i <= n; i++) {
			logs[i] = logs[i >> 1] + 1;
		}
		f.resize(logs[n] + 1);
		for (int i = 0; i < f.size(); ++i) {
			f[i].resize(n - i);
			for (int j = 0; j + (1 << i) - 1 < n; ++j)
				if (!i) f[i][j] = data[j];
				else f[i][j] = std::min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}
	}
	
	T query(int l, int r) {
		int s = logs[r - l + 1];
		return std::min(f[s][l], f[s][r - (1 << s) + 1]);
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];

	SparseTable<int> st(arr);
	
	for (int i = 0; i < n - m + 1; i++) {
		cout << st.query(i, i + m - 1) << "\n";
	} 
	return 0;
}
