#include <bits/stdc++.h>
using namespace std;


/**
 * LazySegmentTree supporting XOR
 * Lazy tag set to 0 or 1 representing if XOR should be applied
 */
template <typename T>
struct LazySegmentTree {
	struct Node {
		int start, end;
		T lazy, val;
	};

	std::vector<Node> t;
	int size;

	LazySegmentTree(int size): size(size) {
		t.resize(size * 4);
		_build(1, 0, size - 1);
	}

	LazySegmentTree(const std::vector<int>& data): size(data.size()) {
		t.resize(size * 4);
		_build(1, 0, size - 1, data);
	}

	void _build(int i, int start, int end, const std::vector<int>& data = std::vector<int>()) {
		t[i].start = start;
		t[i].end = end;
		if (start == end) {
			if (data.size()) t[i].val = data[start];
		} else {
			int mid = (start + end) >> 1;
			_build(i << 1, start, mid, data);
			_build(i << 1 | 1, mid + 1, end, data);
			if (data.size())
				_push_up(i);
		}
	}

	void _push_up(int i) {
		t[i].val = t[i << 1].val + t[i << 1 | 1].val;
	}

	void _push_down(int i) {
		if (t[i].lazy) {
			// flip bits
			t[i << 1].val = (t[i << 1].end - t[i << 1].start + 1) - t[i << 1].val;
			t[i << 1 | 1].val = (t[i << 1 | 1].end - t[i << 1 | 1].start + 1) - t[i << 1 | 1].val;
			t[i << 1].lazy ^= 1;
			t[i << 1 | 1].lazy ^= 1;
			t[i].lazy = 0;
		}
	}

	// flip bits to range [l, r]
	void update(int l, int r, int i = 1) {
		if (l <= t[i].start && r >= t[i].end) {
			// flip: length - current sum
			t[i].val = (t[i].end - t[i].start + 1) - t[i].val;
			t[i].lazy ^= 1;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (l <= mid) update(l, r, i << 1);
		if (r > mid) update(l, r, i << 1 | 1);
		_push_up(i);
	}

	T query(int l, int r, int i = 1) {
		if (l <= t[i].start && r >= t[i].end)
			return t[i].val;
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		T res = 0;
		if (l <= mid) res += query(l, r, i << 1);
		if (r > mid) res += query(l, r, i << 1 | 1);
		return res;
	}
};



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	const int MAX_N = ceil(log2(1e6));	// # bits
	int n, m;
	cin >> n;
	
	vector<vector<int>> binary(MAX_N, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		int x, j = 0;
		cin >> x;
		while (x) {
			binary[j][i] = x & 1;
			x = x >> 1;
			j++;
		}
	}

	
	// trees[i]: the bits of factor 2^i
	vector<LazySegmentTree<long long>> trees;
	for (int i = 0; i < MAX_N; i++) {
		trees.push_back(LazySegmentTree<long long>(binary[i]));
	}

	cin >> m;
	while (m--) {
		int op, l, r, x;
		cin >> op >> l >> r;
		l--; r--;
		if (op == 1) {
			long long res = 0;
			for (int i = 0; i < MAX_N; i++) {
				res += (1 << i) * trees[i].query(l, r);
			}
			cout << res << "\n";
		} else {
			cin >> x;
			int i = 0;
			while (x) {
				if (x & 1) {
					trees[i].update(l, r);
				}
				x = x >> 1;
				i++;
			}
		}
	}
	return 0;
}
