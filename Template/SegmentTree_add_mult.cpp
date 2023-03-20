#include <vector>


/**
 * LazySegmentTree supporting + and *
 * 0-indexed, supporting single modify, range update & query
 */
template <typename T, T MOD>
struct LazySegmentTree {
	struct Node {
		int start, end;
		T lazy_add, lazy_mul, val;
	};
	
	std::vector<Node> t;
	int size;

	LazySegmentTree(int size): size(size) {
		t.resize(size << 2);
		_build(1, 0, size - 1);
	}

	LazySegmentTree(const std::vector<int>& data): size(data.size()) {
		t.resize(size << 2);
		_build(1, 0, size - 1, data);
	}

	void _build(int i, int start, int end, const std::vector<int>& data = std::vector<T>()) {
		t[i].start = start;
		t[i].end = end;
		t[i].lazy_mul = 1;
		if (start == end) {
			if (data.size()) t[i].val = data[start] % MOD;
		} else {
			int mid = (start + end) >> 1;
			_build(i << 1, start, mid, data);
			_build(i << 1 | 1, mid + 1, end, data);
			if (data.size())
				_push_up(i);
		}
	}

	void _push_up(int i) {
		t[i].val = (t[i << 1].val + t[i << 1 | 1].val) % MOD;
	}

	void _push_down(int i) {
		if (t[i].lazy_add || t[i].lazy_mul != 1) {
			// important: multiplication before addition
			t[i << 1].val = (
				(t[i].lazy_mul * t[i << 1].val) % MOD + 
				(((t[i << 1].end - t[i << 1].start + 1) * t[i].lazy_add) % MOD)
			) % MOD;
			t[i << 1 | 1].val = (
				(t[i].lazy_mul * t[i << 1 | 1].val) % MOD + 
				(((t[i << 1 | 1].end - t[i << 1 | 1].start + 1) * t[i].lazy_add) % MOD)
			) % MOD;
			
			t[i << 1].lazy_mul = (t[i << 1].lazy_mul * t[i].lazy_mul) % MOD;
			t[i << 1 | 1].lazy_mul = (t[i << 1 | 1].lazy_mul * t[i].lazy_mul) % MOD;
			// important: multiply the add lazy node first
			t[i << 1].lazy_add = (t[i << 1].lazy_add * t[i].lazy_mul + t[i].lazy_add) % MOD;
			t[i << 1 | 1].lazy_add = (t[i << 1 | 1].lazy_add * t[i].lazy_mul + t[i].lazy_add) % MOD;

			t[i].lazy_mul = 1;
			t[i].lazy_add = 0;
		}
	}

	// add delta to range [l, r]
	void add(int l, int r, T delta, int i = 1) {
		if (l <= t[i].start && r >= t[i].end) {
			t[i].val = (t[i].val + delta * (t[i].end - t[i].start + 1)) % MOD;
			t[i].lazy_add = (t[i].lazy_add + delta) % MOD;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (l <= mid) add(l, r, delta, i << 1);
		if (r > mid) add(l, r, delta, i << 1 | 1);
		_push_up(i);
	}

	// multiply sigma to range [l, r]
	void mult(int l, int r, T sigma, int i = 1) {
		if (l <= t[i].start && r >= t[i].end) {
			// important: need to multiply the current lazy as well
			t[i].val = (t[i].val * sigma) % MOD;
			t[i].lazy_add = (t[i].lazy_add * sigma) % MOD;
			t[i].lazy_mul = (t[i].lazy_mul * sigma) % MOD;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (l <= mid) mult(l, r, sigma, i << 1);
		if (r > mid) mult(l, r, sigma, i << 1 | 1);
		_push_up(i);
	}

	T query(int l, int r, int i = 1) {
		if (l <= t[i].start && r >= t[i].end)
			return t[i].val;
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		T res = 0;
		if (l <= mid) res = (res + query(l, r, i << 1)) % MOD;
		if (r > mid) res = (res + query(l, r, i << 1 | 1)) % MOD;
		return res;
	}
};
