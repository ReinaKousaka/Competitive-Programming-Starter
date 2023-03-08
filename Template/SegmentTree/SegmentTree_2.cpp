#include <vector>

// LazySegmentTree supporting +
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
        build(1, 1, size);
    }

    LazySegmentTree(const std::vector<int>& data): size(data.size()) {
        tree.resize(size * 4 + 1);
        build(1, 1, size, data);
    }

    void build(int i, int start, int end, const std::vector<int>& data = std::vector<int>()) {
        tree[i].start = start;
        tree[i].end = end;
        if (start == end) {
            // caution: assume data is 0-indexed here
            if (data.size()) tree[i].val = data[start - 1];
        } else {
            int mid = (start + end) >> 1;
            build(i << 1, start, mid, data);
            build(i << 1 | 1, mid + 1, end, data);
            if (data.size())
                tree[i].val = tree[i << 1].val + tree[i << 1 | 1].val;
        }
    }

    void _push_down(int i) {
        if (tree[i].lazy) {
            // can adjust operator
            tree[i << 1].val += tree[i].lazy * (tree[i << 1].end - tree[i << 1].start + 1);
            tree[i << 1 | 1].val += tree[i].lazy * (tree[i << 1 | 1].end - tree[i << 1 | 1].start + 1);
            tree[i << 1].lazy += tree[i].lazy;
            tree[i << 1 | 1].lazy += tree[i].lazy;
            tree[i].lazy = 0;
        }
    }

    // add delta to range [l, r]
    void update(int l, int r, T delta, int i = 1) {
        // if current node is covered
        if (l <= tree[i].start && r >= tree[i].end) {
            tree[i].val = tree[i].val + delta * (tree[i].end - tree[i].start + 1);
            tree[i].lazy += delta;
            return;
        }
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        if (l <= mid) update(l, r, delta, i << 1);
        if (r > mid) update(l, r, delta, i << 1 | 1);
        tree[i].val = tree[i << 1].val + tree[i << 1 | 1].val;
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
