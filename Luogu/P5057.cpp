#include <vector>
#include <iostream>
using namespace std;


/**
 * LazySegmentTree supporting +
 * 0-indexed, supporting single modify, range update & query
 */
template <typename T>
struct LazySegmentTree {
	struct Node {
		int start, end;
		T lazy, val;
	};

	std::vector<Node> tree;
	int size;

	LazySegmentTree(int size): size(size) {
		tree.resize(size * 4 + 1);
		build(1, 0, size - 1);
	}

	LazySegmentTree(const std::vector<int>& data): size(data.size()) {
		tree.resize(size * 4 + 1);
		build(1, 0, size - 1, data);
	}

	void build(int i, int start, int end, const std::vector<int>& data = std::vector<int>()) {
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
		tree[i].val = tree[i << 1].val + tree[i << 1 | 1].val;
	}

	void _push_down(int i) {
		if (tree[i].lazy) {
			tree[i << 1].val += tree[i].lazy * (tree[i << 1].end - tree[i << 1].start + 1);
			tree[i << 1 | 1].val += tree[i].lazy * (tree[i << 1 | 1].end - tree[i << 1 | 1].start + 1);
			tree[i << 1].lazy += tree[i].lazy;
			tree[i << 1 | 1].lazy += tree[i].lazy;
			tree[i].lazy = 0;
		}
	}

	// add delta to range [l, r]
	void update(int l, int r, T delta, int i = 1) {
		if (l <= tree[i].start && r >= tree[i].end) {
			tree[i].val = tree[i].val + delta * (tree[i].end - tree[i].start + 1);
			tree[i].lazy += delta;
			return;
		}
		_push_down(i);
		int mid = (tree[i].start + tree[i].end) >> 1;
		if (l <= mid) update(l, r, delta, i << 1);
		if (r > mid) update(l, r, delta, i << 1 | 1);
		_push_up(i);
	}

	// set single element to new_val
	void set(int idx, T new_val, int i = 1) {
		if (idx == tree[i].start && idx == tree[i].end) {
			tree[i].val = new_val;
			return;
		}
		_push_down(i);
		int mid = (tree[i].start + tree[i].end) >> 1;
		if (idx <= mid) set(idx, new_val, i << 1);
		else set(idx, new_val, i << 1 | 1);
		_push_up(i);
	}

	T query(int l, int r, int i = 1) {
		if (l <= tree[i].start && r >= tree[i].end)
			return tree[i].val;
		_push_down(i);
		int mid = (tree[i].start + tree[i].end) >> 1;
		T res = 0;
		if (l <= mid) res += query(l, r, i << 1);
		if (r > mid) res += query(l, r, i << 1 | 1);
		return res;
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	LazySegmentTree<int> seg(n);

	while(m--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			seg.update(l - 1, r - 1, 1);
		} else {
			int i;
			cin >> i;
			cout << seg.query(i - 1, i - 1) % 2 << "\n";
		}
	}
	return 0;
}