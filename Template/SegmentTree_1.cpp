#include <vector>


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
			t[i << 1].val += t[i].lazy * (t[i << 1].end - t[i << 1].start + 1);
			t[i << 1 | 1].val += t[i].lazy * (t[i << 1 | 1].end - t[i << 1 | 1].start + 1);
			t[i << 1].lazy += t[i].lazy;
			t[i << 1 | 1].lazy += t[i].lazy;
			t[i].lazy = 0;
		}
	}

	// add delta to range [l, r]
	void update(int l, int r, T delta, int i = 1) {
		if (l <= t[i].start && r >= t[i].end) {
			t[i].val = t[i].val + delta * (t[i].end - t[i].start + 1);
			t[i].lazy += delta;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (l <= mid) update(l, r, delta, i << 1);
		if (r > mid) update(l, r, delta, i << 1 | 1);
		_push_up(i);
	}

	// set single element to new_val
	void set(int idx, T new_val, int i = 1) {
		if (idx == t[i].start && idx == t[i].end) {
			t[i].val = new_val;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (idx <= mid) set(idx, new_val, i << 1);
		else set(idx, new_val, i << 1 | 1);
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
