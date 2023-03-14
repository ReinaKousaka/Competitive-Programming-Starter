#include <bits/stdc++.h>
using namespace std;


int MOD;

// Segment Tree for *, only need to read root value
template <typename T>
struct SegmentTree {
	struct Node {
		int start, end;
		T val;
	};

	std::vector<Node> tree;
	int size;

	SegmentTree(int size): size(size) {
		tree.resize(size * 4);
		build(1, 0, size - 1);
	}

	SegmentTree(const std::vector<T>& data): size(data.size()) {
		tree.resize(size * 4);
		build(1, 0, size - 1, data);
	}

	void build(int i, int start, int end, const std::vector<T>& data = std::vector<int>()) {
		tree[i].start = start;
		tree[i].end = end;
		if (start == end) {
			if (data.size()) tree[i].val = data[start];
		} else {
			int mid = (start + end) >> 1;
			build(i << 1, start, mid, data);
			build(i << 1 | 1, mid + 1, end, data);
			if (data.size())
				_push_up(i);
		}
	}

	void _push_up(int i) {
		tree[i].val = (tree[i << 1].val * tree[i << 1 | 1].val) % MOD;
	}

	// set idx-th element to new_val
	void set(int idx, T new_val, int i = 1) {
		if (idx == tree[i].start && idx == tree[i].end) {
			tree[i].val = new_val;
			return;
		}
		int mid = (tree[i].start + tree[i].end) >> 1;
		if (idx <= mid) set(idx, new_val, i << 1);
		if (idx > mid) set(idx, new_val, i << 1 | 1);
		_push_up(i);
	}
};



void solve() {
	int q;
	cin >> q >> MOD;

	SegmentTree<long long> seg(vector<long long> (q, 1));

	for (int i = 0; i < q; i++) {
		int op, m;
		cin >> op >> m;
		if (op == 1) {
			seg.set(i, m);
		} else {
			seg.set(m - 1, 1);		// 0-indexed seg tree
		}
		cout << seg.tree[1].val << "\n";
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
