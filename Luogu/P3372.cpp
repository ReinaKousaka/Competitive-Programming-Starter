#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// LazySegmentTree supporting +
template <typename T>
class LazySegmentTreeNode {
public:
    int start, end;
    T lazy, val;
};

template <typename T>
class LazySegmentTree {
public:
    std::vector<LazySegmentTreeNode<T>> tree;
    int size;

    LazySegmentTree(int size): size(size) {
        tree.resize(size * 4 + 1);
        build(1, 1, size);
    }

    LazySegmentTree(const std::vector<T>& data): size(data.size()) {
        tree.resize(size * 4 + 1);
        build(1, 1, size, data);
    }

    void build(int i, int start, int end, const std::vector<T>& data = std::vector<T>()) {
        tree[i].start = start;
        tree[i].end = end;
        if (start == end) {
            // caution: assume data is 0-indexed here
            if (data.size()) tree[i].val = data[start - 1];
        } else {
            int mid = (start + end) >> 1;
            build(i * 2, start, mid, data);
            build(i * 2 + 1, mid + 1, end, data);
            if (data.size())
                // can adjust operator
                tree[i].val = tree[i * 2].val + tree[i * 2 + 1].val;
        }
    }

    void _push_down(int i) {
        if (tree[i].lazy) {
            // can adjust operator
            tree[i * 2].val += tree[i].lazy * (tree[i * 2].end - tree[i * 2].start + 1);
            tree[i * 2 + 1].val += tree[i].lazy * (tree[i * 2 + 1].end - tree[i * 2 + 1].start + 1);
            tree[i * 2].lazy += tree[i].lazy;
            tree[i * 2 + 1].lazy += tree[i].lazy;
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
        if (l <= mid) update(l, r, delta, i * 2);
        if (r > mid) update(l, r, delta, i * 2 + 1);
        tree[i].val = tree[i * 2].val + tree[i * 2 + 1].val;
    }

    T query(int l, int r, int i = 1) {
        if (l <= tree[i].start && r >= tree[i].end)
            return tree[i].val;
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        T res = 0;
        if (l <= mid) res += query(l, r, i * 2);
        if (r > mid) res += query(l, r, i * 2 + 1);
        return res;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    LazySegmentTree<ll> seg(arr);
    while (m--) {
        int t, x, y, z;
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> z;
            seg.update(x, y, z);
        } else {
            cin >> x >> y;
            cout << seg.query(x, y) << "\n";
        }
    }
    return 0;
}
