#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int mod;

// LazySegmentTree supporting + and *
template <typename T>
class LazySegmentTreeNode {
public:
    int start, end;
    T lazy_add, lazy_mul, val;
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
        tree[i].lazy_mul = 1;
        if (start == end) {
            // caution: assume data is 0-indexed here
            if (data.size()) tree[i].val = data[start - 1] % mod;
        } else {
            int mid = (start + end) >> 1;
            build(i * 2, start, mid, data);
            build(i * 2 + 1, mid + 1, end, data);
            if (data.size())
                tree[i].val = (tree[i * 2].val + tree[i * 2 + 1].val) % mod;
        }
    }

    void _push_down(int i) {
        if (tree[i].lazy_add || tree[i].lazy_mul != 1) {
            // important: multiplication before addition
            tree[i * 2].val = ((tree[i].lazy_mul * tree[i * 2].val) % mod + 
                (((tree[i * 2].end - tree[i * 2].start + 1) * tree[i].lazy_add) % mod)) % mod;
            tree[i * 2 + 1].val = ((tree[i].lazy_mul * tree[i * 2 + 1].val) % mod + 
                (((tree[i * 2 + 1].end - tree[i * 2 + 1].start + 1) * tree[i].lazy_add) % mod)) % mod;
            
            tree[i * 2].lazy_mul = (tree[i * 2].lazy_mul * tree[i].lazy_mul) % mod;
            tree[i * 2 + 1].lazy_mul = (tree[i * 2 + 1].lazy_mul * tree[i].lazy_mul) % mod;
            // important: multiply the add lazy node first
            tree[i * 2].lazy_add = (tree[i * 2].lazy_add * tree[i].lazy_mul + tree[i].lazy_add) % mod;
            tree[i * 2 + 1].lazy_add = (tree[i * 2 + 1].lazy_add * tree[i].lazy_mul + tree[i].lazy_add) % mod;

            tree[i].lazy_mul = 1;
            tree[i].lazy_add = 0;
        }
    }

    // add delta to range [l, r]
    void add(int l, int r, T delta, int i = 1) {
        if (l <= tree[i].start && r >= tree[i].end) {
            tree[i].val = (tree[i].val + delta * (tree[i].end - tree[i].start + 1)) % mod;
            tree[i].lazy_add = (tree[i].lazy_add + delta) % mod;
            return;
        }
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        if (l <= mid) add(l, r, delta, i * 2);
        if (r > mid) add(l, r, delta, i * 2 + 1);
        tree[i].val = (tree[i * 2].val + tree[i * 2 + 1].val) % mod;
    }

    // multiply sigma to range [l, r]
    void mult(int l, int r, T sigma, int i = 1) {
        if (l <= tree[i].start && r >= tree[i].end) {
            // important: need to multiply the current lazy as well
            tree[i].val = (tree[i].val * sigma) % mod;
            tree[i].lazy_add = (tree[i].lazy_add * sigma) % mod;
            tree[i].lazy_mul = (tree[i].lazy_mul * sigma) % mod;
            return;
        }
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        if (l <= mid) mult(l, r, sigma, i * 2);
        if (r > mid) mult(l, r, sigma, i * 2 + 1);
        tree[i].val = (tree[i * 2].val + tree[i * 2 + 1].val) % mod;
    }

    T query(int l, int r, int i = 1) {
        if (l <= tree[i].start && r >= tree[i].end)
            return tree[i].val;
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        T res = 0;
        if (l <= mid) res = (res + query(l, r, i * 2)) % mod;
        if (r > mid) res = (res + query(l, r, i * 2 + 1)) % mod;
        return res;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> mod;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    
    LazySegmentTree<ll> seg(arr);
    while (m--) {
        int t, x, y, z;
        cin >> t;
        if (t == 1) {
            cin >> x >> y >> z;
            seg.mult(x, y, z);
        } else if (t == 2) {
            cin >> x >> y >> z;
            seg.add(x, y, z);
        } else {
            cin >> x >> y;
            cout << seg.query(x, y) << "\n";
        }
    }
    return 0;
}
